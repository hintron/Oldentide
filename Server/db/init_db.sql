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
    face text not null default "face0",
    skin text not null default "normal",
    profession text not null default "Adventurer",
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
    strength integer not null default 0,
    constitution integer not null default 0,
    intelligence integer not null default 0,
    dexterity integer not null default 0,
    -- Skills:
    axe integer not null default 0,
    dagger integer not null default 0,
    unarmed integer not null default 0,
    hammer integer not null default 0,
    polearm integer not null default 0,
    spear integer not null default 0,
    staff integer not null default 0,
    sword integer not null default 0,
    archery integer not null default 0,
    crossbow integer not null default 0,
    sling integer not null default 0,
    thrown integer not null default 0,
    armor integer not null default 0,
    dualweapon integer not null default 0,
    shield integer not null default 0,
    bardic integer not null default 0,
    conjuring integer not null default 0,
    druidic integer not null default 0,
    illusion integer not null default 0,
    necromancy integer not null default 0,
    sorcery integer not null default 0,
    shamanic integer not null default 0,
    spellcraft integer not null default 0,
    summoning integer not null default 0,
    focus integer not null default 0,
    armorsmithing integer not null default 0,
    tailoring integer not null default 0,
    fletching integer not null default 0,
    weaponsmithing integer not null default 0,
    alchemy integer not null default 0,
    lapidary integer not null default 0,
    calligraphy integer not null default 0,
    enchanting integer not null default 0,
    herbalism integer not null default 0,
    hunting integer not null default 0,
    mining integer not null default 0,
    bargaining integer not null default 0,
    camping integer not null default 0,
    firstaid integer not null default 0,
    lore integer not null default 0,
    picklocks integer not null default 0,
    scouting integer not null default 0,
    search integer not null default 0,
    stealth integer not null default 0,
    traps integer not null default 0,
    aeolandis integer not null default 0,
    hieroform integer not null default 0,
    highgundis integer not null default 0,
    oldpraxic integer not null default 0,
    praxic integer not null default 0,
    runic integer not null default 0,
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
    zone text not null default "Adventurer's Guild",
    x real not null default 0,
    y real not null default 0,
    z real not null default 0,
    direction real not null default 0.0
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
    face text not null default "face0",
    skin text not null default "normal",
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
    strength integer not null default 0,
    constitution integer not null default 0,
    intelligence integer not null default 0,
    dexterity integer not null default 0,
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
    zone text not null default "The Void",
    x real not null default 0,
    y real not null default 0,
    z real not null default 0,
    direction real not null default 0.0
);

DROP TABLE IF EXISTS items;
CREATE TABLE items (
    id integer not null primary key autoincrement,
    item_template_id integer not null,
    -- entity specific
    player_id integer,
    npc_id integer,
    identified integer not null default 0,
    color text not null default "None",
    item_count not null default 1,
    name text not null
    --FOREIGN KEY(player_id) REFERENCES players(id) ON DELETE CASCADE ON UPDATE CASCADE
    --FOREIGN KEY(npc_id) REFERENCES npcs(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- item templates contain the reference for all possible items in the game.
DROP TABLE IF EXISTS item_templates;
CREATE TABLE item_templates (
    id integer not null primary key autoincrement,
    name text not null,
    true_name text not null,
    lore_level integer not null default 0,
    type text not null,
    slot text not null default "None",
    icon text not null default "Mystery",
    weight real not null default 0,
    encumbrance real not null default 0,
    dyeable integer not null default 0,
    stackable integer not null default 0,
    stack_size integer not null default 1,
    usable integer not null default 0,
    equipable integer not null default 0,
    base_price integer not null default 0,
    strength_requirement integer not null default 0,
    constitution_requirement integer not null default 0,
    intelligence_requirement integer not null default 0,
    dexterity_requirement integer not null default 0,
    skill_type_0 text,
    skill_requirement_0 integer not null default 1,
    skill_type_1 text,
    skill_requirement_1 integer not null default 1,
    skill_type_2 text,
    skill_requirement_2 integer not null default 1,
    skill_type_3 text,
    skill_requirement_3 integer not null default 1,
    skill_type_4 text,
    skill_requirement_4 integer not null default 1,
    description text,
    true_description text
)


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
