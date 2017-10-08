
------------------------
-- Tables
------------------------

DROP TABLE IF EXISTS accounts;
CREATE TABLE accounts (
    id integer not null primary key autoincrement,
    valid integer not null,
    accountname text not null unique collate nocase,
    email text not null collate nocase,
    session text collate nocase,
    playing integer not null,
    key text not null collate nocase,
    salt text not null collate nocase
);

DROP TABLE IF EXISTS players;
CREATE TABLE players (
    id integer not null primary key autoincrement,
    account_id integer,
    -- Identification:
    firstname text not null,
    lastname text not null,
    guild text,
    race text not null,
    gender text not null,
    face text,
    skin text,
    profession text,
    level integer not null default 1,
    -- Stats:
    hp integer not null default 100,
    maxhp integer not null default 100,
    bp integer not null default 0,
    maxbp integer not null default 0,
    mp integer not null default 0,
    maxmp integer not null default 0,
    ep integer not null default 0,
    maxep integer not null default 0,
    strength integer not null default 1,
    constitution integer not null default 1,
    intelligence integer not null default 1,
    dexterity integer not null default 1,
    -- Skills:
    axe integer default 1,
    dagger integer default 1,
    unarmed integer default 1,
    hammer integer default 1,
    polearm integer default 1,
    spear integer default 1,
    staff integer default 1,
    sword integer default 1,
    archery integer default 1,
    crossbow integer default 1,
    sling integer default 1,
    thrown integer default 1,
    armor integer default 1,
    dualweapon integer default 1,
    shield integer default 1,
    bardic integer default 1,
    conjuring integer default 1,
    druidic integer default 1,
    illusion integer default 1,
    necromancy integer default 1,
    sorcery integer default 1,
    shamanic integer default 1,
    spellcraft integer default 1,
    summoning integer default 1,
    focus integer default 1,
    armorsmithing integer default 1,
    tailoring integer default 1,
    fletching integer default 1,
    weaponsmithing integer default 1,
    alchemy integer default 1,
    lapidary integer default 1,
    calligraphy integer default 1,
    enchanting integer default 1,
    herbalism integer default 1,
    hunting integer default 1,
    mining integer default 1,
    bargaining integer default 1,
    camping integer default 1,
    firstaid integer default 1,
    lore integer default 1,
    picklocks integer default 1,
    scouting integer default 1,
    search integer default 1,
    stealth integer default 1,
    traps integer default 1,
    aeolandis integer default 1,
    hieroform integer default 1,
    highgundis integer default 1,
    oldpraxic integer default 1,
    praxic integer default 1,
    runic integer default 1,
    -- Equipment:
    head text,
    chest text,
    arms text,
    hands text,
    legs text,
    feet text,
    cloak text,
    necklace text,
    ringone text,
    ringtwo text,
    righthand text,
    lefthand text,
    -- Location:
    zone text,
    x real,
    y real,
    z real,
    pitch real,
    yaw real
);


-- NPCs will have the same fields as player, except for account_id and the skills section
DROP TABLE IF EXISTS npcs;
CREATE TABLE npcs (
    id integer not null primary key autoincrement,
    -- Identification:
    firstname text not null,
    lastname text not null,
    guild text,
    race text not null,
    gender text not null,
    face text,
    skin text,
    profession text,
    level integer not null default 1,
    -- Stats:
    hp integer not null default 100,
    maxhp integer not null default 100,
    bp integer not null default 0,
    maxbp integer not null default 0,
    mp integer not null default 0,
    maxmp integer not null default 0,
    ep integer not null default 0,
    maxep integer not null default 0,
    strength integer not null default 1,
    constitution integer not null default 1,
    intelligence integer not null default 1,
    dexterity integer not null default 1,
    -- Equipment:
    head text,
    chest text,
    arms text,
    hands text,
    legs text,
    feet text,
    cloak text,
    necklace text,
    ringone text,
    ringtwo text,
    righthand text,
    lefthand text,
    -- Location:
    zone text,
    x real,
    y real,
    z real,
    pitch real,
    yaw real
);

DROP TABLE IF EXISTS items;
CREATE TABLE items (
    id integer not null primary key autoincrement,
    -- only one of the following two fields should be populated at a time
    player_id integer,
    npc_id integer,
    name text not null,
    location text not null,
    weight real not null,
    equip integer not null,
    use integer not null,
    x integer,
    y integer,

    FOREIGN KEY(player_id) REFERENCES players(id) ON DELETE CASCADE ON UPDATE CASCADE
    FOREIGN KEY(npc_id) REFERENCES npcs(id) ON DELETE CASCADE ON UPDATE CASCADE
);



------------------------
-- Views
------------------------

DROP VIEW IF EXISTS view_players;
CREATE VIEW view_players AS
SELECT
    *
FROM players
LEFT JOIN accounts on players.account_id = accounts.id
;


-- Show all the items currently being possessed by players
DROP VIEW IF EXISTS view_items_player;
CREATE VIEW view_items_player AS
SELECT
    *
FROM items
LEFT JOIN players on items.player_id = players.id
WHERE player_id IS NOT NULL
;

-- Show all the items currently being possessed by npcs
DROP VIEW IF EXISTS view_items_npc;
CREATE VIEW view_items_npc AS
SELECT
    *
FROM items
LEFT JOIN npcs on items.npc_id = npcs.id
WHERE npc_id IS NOT NULL
;

-- References
-- How object-oriented class inheritance does NOT fit with sql schemas
-- https://stackoverflow.com/a/193222