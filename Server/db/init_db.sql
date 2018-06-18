------------------------
-- Tables
------------------------

DROP TABLE IF EXISTS accounts;
CREATE TABLE accounts (
    id integer not null primary key autoincrement,
    valid integer not null,
    banned integer not null default 0,
    accountname text not null unique collate nocase,
    email text not null unique collate nocase,
    gamesession integer not null,
    playing integer not null,
    verify text not null unique,
    hash text not null collate nocase,
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
    alive int not null default 1,
    plevel integer not null default 1,
    dp integer not null default 0,
    -- Stats:
    hp integer not null default 1,
    maxhp integer not null default 1,
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
    axe integer default 0,
    dagger integer default 0,
    unarmed integer default 0,
    hammer integer default 0,
    polearm integer default 0,
    spear integer default 0,
    staff integer default 0,
    sword integer default 0,
    archery integer default 0,
    crossbow integer default 0,
    sling integer default 0,
    thrown integer default 0,
    armor integer default 0,
    dualweapon integer default 0,
    shield integer default 0,
    bardic integer default 0,
    conjuring integer default 0,
    druidic integer default 0,
    illusion integer default 0,
    necromancy integer default 0,
    sorcery integer default 0,
    shamanic integer default 0,
    spellcraft integer default 0,
    summoning integer default 0,
    focus integer default 0,
    armorsmithing integer default 0,
    tailoring integer default 0,
    fletching integer default 0,
    weaponsmithing integer default 0,
    alchemy integer default 0,
    lapidary integer default 0,
    calligraphy integer default 0,
    enchanting integer default 0,
    herbalism integer default 0,
    hunting integer default 0,
    mining integer default 0,
    bargaining integer default 0,
    camping integer default 0,
    firstaid integer default 0,
    lore integer default 0,
    picklocks integer default 0,
    scouting integer default 0,
    search integer default 0,
    stealth integer default 0,
    traps integer default 0,
    aeolandis integer default 0,
    hieroform integer default 0,
    highgundis integer default 0,
    oldpraxic integer default 0,
    praxic integer default 0,
    runic integer default 0,
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
    direction real
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
    alive int not null default 1,
    nlevel integer not null default 1,
    -- Stats:
    hp integer not null default 1,
    maxhp integer not null default 1,
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
    righthand text,
    lefthand text,
    -- Location:
    zone text,
    x real,
    y real,
    z real,
    direction real
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
    y integer
    --FOREIGN KEY(player_id) REFERENCES players(id) ON DELETE CASCADE ON UPDATE CASCADE
    --FOREIGN KEY(npc_id) REFERENCES npcs(id) ON DELETE CASCADE ON UPDATE CASCADE
);



------------------------
-- Views
------------------------

--DROP VIEW IF EXISTS view_players;
--CREATE VIEW view_players AS
--SELECT
--    *
--FROM players
--LEFT JOIN accounts on players.account_id = accounts.id
--;


-- Show all the items currently being possessed by players
--DROP VIEW IF EXISTS view_items_player;
--CREATE VIEW view_items_player AS
--SELECT
--    *
--FROM items
--LEFT JOIN players on items.player_id = players.id
--WHERE player_id IS NOT NULL
--;

-- Show all the items currently being possessed by npcs
--DROP VIEW IF EXISTS view_items_npc;
--CREATE VIEW view_items_npc AS
--SELECT
--    *
--FROM items
--LEFT JOIN npcs on items.npc_id = npcs.id
--WHERE npc_id IS NOT NULL
--;
