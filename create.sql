-- Create the `users` table
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    rfid TEXT NOT NULL,
    name TEXT NOT NULL,
    group_id TEXT NOT NULL
);

-- Create the `accessusers` table
CREATE TABLE accessusers (
    id INTEGER PRIMARY KEY,
    rfid TEXT NOT NULL,
    day INTEGER NOT NULL,
    month INTEGER NOT NULL,
    year INTEGER NOT NULL,
    hour INTEGER NOT NULL,
    minute INTEGER NOT NULL,
    second INTEGER NOT NULL,
    group_id TEXT NOT NULL
);

-- Insert records into the `users` table
INSERT INTO users (id, rfid, name, group_id) VALUES
    (1, 'a305cd0b60', 'John', 'g'),
    (2, '73051e99f1', 'Mike', 'd');

-- Insert records into the `accessusers` table
INSERT INTO accessusers (id, rfid, day, month, year, hour, minute, second, group_id) VALUES
    (1, 'a305cd0b60', 16, 3, 2024, 19, 51, 15, 'g'),
    (2, '73051e99f1', 16, 3, 2024, 19, 51, 52, 'd'),
    (3, 'a305cd0b60', 28, 3, 2024, 17, 46, 59, 'g'),
    (4, '132bc70cf3', 29, 3, 2024, 17, 0, 16, 'n');

