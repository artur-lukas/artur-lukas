import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
        user_id
    )

    rows = db.execute(
        "SELECT cash FROM users WHERE id = ?",
        user_id
    )

    cash = rows[0]["cash"]

    total = cash

    for stock in stocks:
        quote = lookup(stock["symbol"])

        if quote is not None:
            stock["name"] = quote["name"]
            stock["price"] = quote["price"]
            stock["total"] = stock["shares"] * stock["price"]
            total += stock["total"]

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")

        if not shares_input:
            return apology("must provide number of shares")

        try:
            shares = int(shares_input)
        except ValueError:
            return apology("shares must be a whole number")

        if shares <= 0:
            return apology("shares must be positive")

        quote = lookup(symbol)

        if not quote:
            return apology("invalid symbol")

        price = quote["price"]
        total_cost = shares * price

        user_id = session["user_id"]

        rows = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id
        )

        cash = rows[0]["cash"]

        if cash < total_cost:
            return apology("can't afford")

        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id
        )

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, quote["symbol"], shares, price
        )

        flash("Purchase successful!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ? ORDER BY transacted DESC",
        session["user_id"]
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol")

        quote = lookup(symbol)

        if not quote:
            return apology("invalid symbol")

        return render_template("quote2.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if password != confirmation:
            return apology("passwords must match")

        hash_value = generate_password_hash(password)

        username = request.form.get("username")

        try:
            user_id = db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_value
            )
        except ValueError:
            return apology("username already exists")

        session["user_id"] = user_id
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")

        if not shares_input:
            return apology("must provide number of shares")

        try:
            shares = int(shares_input)
        except ValueError:
            return apology("shares must be a whole number")

        if shares <= 0:
            return apology("shares must be positive")

        rows = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ?",
            user_id, symbol
        )

        owned_shares = rows[0]["shares"]

        if owned_shares is None or shares > owned_shares:
            return apology("not enough shares")

        quote = lookup(symbol)

        if quote is None:
            return apology("invalid symbol")

        price = quote["price"]
        sale_value = shares * price

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            sale_value, user_id
        )

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, quote["symbol"], -shares, price
        )

        flash("Sold!")
        return redirect("/")
    else:
        return render_template("sell.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change password"""

    if request.method == "GET":
        return render_template("change_password.html")

    old_password = request.form.get("old_password")
    new_password = request.form.get("new_password")
    confirmation = request.form.get("confirmation")

    if not old_password:
        return apology("must provide current password")

    if not new_password:
        return apology("must provide new password")

    if not confirmation:
        return apology("must confirm new password")

    if new_password != confirmation:
        return apology("new passwords must match")

    rows = db.execute(
        "SELECT hash FROM users WHERE id = ?",
        session["user_id"]
    )

    if not check_password_hash(rows[0]["hash"], old_password):
        return apology("current password is incorrect", 403)

    new_hash = generate_password_hash(new_password)

    db.execute(
        "UPDATE users SET hash = ? WHERE id = ?",
        new_hash, session["user_id"]
    )

    flash("Password changed!")
    return redirect("/")
