-- Keep a log of any SQL queries you execute as you solve the mystery.

--Getting all info  of crime scene
SELECT *
FROM crime_scene_reports
WHERE year = 2025 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
/*output
+-------+--------+-------+-------+----------------------+------------------------------------------------------------------------+
|  id   |  year  | month |  day  |        street        |                              description                               |
+-------+--------+-------+-------+----------------------+------------------------------------------------------------------------+
| 295   | 2025   | 7     | 28    | Humphrey Street      | Theft of the CS50 duck took place at 10:15am at the Humphrey Street ba |
|       |        |       |       |                      | kery. Interviews were conducted today with three witnesses who were pr |
|       |        |       |       |                      | esent at the time – each of their interview transcripts mentions the b |
|       |        |       |       |                      | akery.                                                                 |
+-------+--------+-------+-------+----------------------+------------------------------------------------------------------------+
| 297   | 2025   | 7     | 28    | Humphrey Street      | Littering took place at 16:36. No known witnesses.                     |
+-------+--------+-------+-------+----------------------+------------------------------------------------------------------------+
*/
--Getting all infos about bakery_security_logs
SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10;
/*output
+------+--------+----------+---------------+
| 10   | 8      | entrance | R3G7486       |
| 10   | 14     | entrance | 13FNH73       |
| 10   | 16     | exit     | 5P2BI95       |
| 10   | 18     | exit     | 94KL13X       |
| 10   | 18     | exit     | 6P58WS2       |
| 10   | 19     | exit     | 4328GD8       |
| 10   | 20     | exit     | G412CB7       |
| 10   | 21     | exit     | L93JTIZ       |
| 10   | 23     | exit     | 322W7JE       |
| 10   | 23     | exit     | 0NTHK55       |
| 10   | 35     | exit     | 1106N58       |
| 10   | 42     | entrance | NRYN856       |
| 10   | 44     | entrance | WD5M8I6       |
| 10   | 55     | entrance | V47T75I       |
+------+--------+----------+---------------+
*/
--Getting all infos about the interviews that were taken on the day of the theft and which concern the bakery
SELECT name, transcript
FROM interviews
WHERE year = 2025 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
/*output
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|  name   |                                                                                                                                                     transcript                                                                                                                                                      |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/
--checking earliest flight out of the city
SELECT flights.id, flights.destination_airport_id, flights.hour, flights.minute
FROM flights
Join airports ON airports.id = flights.origin_airport_id
WHERE airports.city = 'Fiftyville' AND flights.year = 2025 AND flights.month = 7 AND flights.day = 29
ORDER BY flights.hour, flights.minute
Limit 3;
/*output
+----+------------------------+------+--------+
| id | destination_airport_id | hour | minute |
+----+------------------------+------+--------+
| 36 | 4                      | 8    | 20     |
| 43 | 1                      | 9    | 30     |
| 23 | 11                     | 12   | 15     |
+----+------------------------+------+--------+
*/
--getting the name of the destination airport with the id
SELECT city
FROM airports
WHERE id = 4;
/*output
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/
--info of atm transaction (withdrawing) on the Leggett Street around the time of the theft
SELECT id, account_number, amount
FROM atm_transactions
WHERE year = 2025 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
/*output
+-----+----------------+--------+
| id  | account_number | amount |
+-----+----------------+--------+
| 246 | 28500762       | 48     |
| 264 | 28296815       | 20     |
| 266 | 76054385       | 60     |
| 267 | 49610011       | 50     |
| 269 | 16153065       | 80     |
| 288 | 25506511       | 20     |
| 313 | 81061156       | 30     |
| 336 | 26013199       | 35     |
+-----+----------------+--------+
*/
--find out who the thief is with atm account number(list above) and passagner list of the flight(id:36) and
--the checking license plate (of bakery_security_logs) for a match between the time of 15 and 25 minuts who drive away
SELECT id, name
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
)
AND id IN(
    SELECT person_id
    FROM bank_accounts
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.year = 2025 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
)
AND license_plate IN(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit'
);
/*output
+--------+-------+
|   id   | name  |
+--------+-------+
| 467400 | Luca  |
| 686048 | Bruce |
+--------+-------+
*/
--checking their calls
SELECT people.name caller, receiver, duration
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2025 AND month = 7 AND day = 28
AND caller IN(
    SELECT phone_number
    FROM people
    WHERE id = 467400 OR id = 686048
);
/*output
+--------+----------------+----------+
| caller |    receiver    | duration |
+--------+----------------+----------+
| Bruce  | (375) 555-8161 | 45       |
| Bruce  | (344) 555-9601 | 120      |
| Bruce  | (022) 555-4052 | 241      |
| Bruce  | (704) 555-5790 | 75       |
+--------+----------------+----------+
*/
--checking the receivers of the calls from Bruce call duration was less than a minute
SELECT name
FROM people
WHERE phone_number IN(
    SELECT receiver
    FROM phone_calls
    JOIN people ON phone_calls.caller = people.phone_number
    WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60
    AND caller IN(
        SELECT phone_number
        FROM people
        WHERE id = 686048
    )
);
/*output
+-------+
| name  |
+-------+
| Robin |
+-------+
*/
