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

-- Characters is the parent table of both npcs and players (pcs)
DROP TABLE IF EXISTS characters;
CREATE TABLE characters (
    -- Identification:
    id integer not null primary key autoincrement,
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

DROP TABLE IF EXISTS players;
CREATE TABLE players (
    id integer not null primary key autoincrement,
    character_id integer not null,
    account_id integer,
    -- TODO: Add in other player-specific fields

    FOREIGN KEY(character_id) REFERENCES characters(id)
);

DROP TABLE IF EXISTS npcs;
CREATE TABLE npcs (
    id integer not null primary key autoincrement,
    character_id integer not null,
    -- TODO: Add in npc-specific fields

    FOREIGN KEY(character_id) REFERENCES characters(id)
);

DROP TABLE IF EXISTS items;
CREATE TABLE items (
    id integer not null primary key autoincrement,
    character_id integer not null,
    name text not null,
    location text not null,
    weight real not null,
    equip integer not null,
    use integer not null,
    x integer not null,
    y integer not null,

    FOREIGN KEY(character_id) REFERENCES characters(id)
);



-- Views


DROP VIEW IF EXISTS players_view;
CREATE VIEW players_view AS
SELECT
    *
FROM players
left join
    characters on players.character_id = characters.id
;


DROP VIEW IF EXISTS npcs_view;
CREATE VIEW npcs_view AS
SELECT
    *
FROM npcs
left join
    characters on npcs.character_id = characters.id
;