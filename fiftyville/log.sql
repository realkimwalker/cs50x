-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Theft happens at 10:15am at bakery, All 3 witnesses -> Interview_transcripts mention bakery
SELECT * FROM crime_scene_reports WHERE MONTH = 7 AND DAY = 28;

-- Filter transcripts that mention bakery
SELECT * FROM interviews WHERE transcript LIKE '%bakery%' AND MONTH = 7 AND DAY = 28;

-- Ruth said theif got into car within 10 minutes of 10:15 (10 results with license plates, entry/exit)
SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2023
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 0 AND 25 AND activity = 'exit';

-- Gives us 8 accound numbers, person id, match from with withdraws on Legget St
SELECT people.name, atm_transactions.transaction_type FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.MONTH = 7
AND atm_transactions.DAY = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Theif's call to accomplice was less than 60 seconds with callers names adde
-- Add names to caller, receiver table
UPDATE phone_calls
SET caller_name = people.name
FROM people
WHERE phone_calls.caller = people.phone_number;

UPDATE phone_calls
SET receiver_name = people.name
FROM people
WHERE phone_calls.receiver = people.phone_number;

SELECT caller, caller_name, receiver, receiver_name FROM phone_calls
WHERE YEAR = 2023
AND MONTH = 7
AND DAY = 28
AND duration < 60;

-- Show flights and airports by name and destination and origin cities
UPDATE flights
SET origin_airport_id = airports.city
FROM airports
WHERE flights.origin_airport_id = airports.id;

UPDATE flights
SET destination_airport_id = airports.city
FROM airports
WHERE flights.destination_aiport_id = airports.id;

SELECT id, hour, minute, origin_airport_id, destination_airport_id
FROM flights
WHERE MONTH = 7
AND DAY = 29
ORDER BY hour ASC
LIMIT 1;

-- See flights to New York City
SELECT flights.destination_airport_id, name, phone_number, license_plate
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 36
ORDER BY flights.hour ASC;

-- Query which suspect appears in all four tables
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE (flights.MONTH = 7 AND flights.DAY = 29 AND flights.id = 36)
AND name IN
(SELECT phone_calls.caller_name
FROM phone_calls
WHERE MONTH = 7 AND DAY = 28 AND duration < 60)
AND name IN
(SELECT people.name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.MONTH = 7
AND atm_transactions.DAY = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
AND name IN
(SELECT people.name
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2023
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 0 AND 25 AND activity = 'exit');
