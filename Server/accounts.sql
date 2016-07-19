DROP TABLE IF EXISTS "accounts";

CREATE TABLE "accounts" (
    `id`    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    `account_name`  TEXT NOT NULL UNIQUE,
    `password`  TEXT NOT NULL,
    `salt`  TEXT NOT NULL,
    `salt_iterations`   NUMERIC NOT NULL,
    `real_name` TEXT
)