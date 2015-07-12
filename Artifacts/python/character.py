#!/usr/bin/python
# Character class to be used in Oldentide.
# Joseph DeVictoria - 2014

import time
from blessings import Terminal

class character:
    def __init__(self, char_account, char_name, char_server):
        self.account = char_account
        self.name = char_name
        self.server = char_server
        self.race = 'human'
        self.gender = 'male'
        self.profession = 'adventurer'
        self.strength = 40
        self.constitution = 40
        self.intelligence = 40
        self.dexterity = 40
        self.level = 1
        self.hppl = 5
        self.mppl = 5
        self.currentHP = 0
        self.maxHP = 0
        self.currentBP = 0
        self.maxBP = 0
        self.currentMP = 0
        self.maxMP = 0
        self.currentEP = 0
        self.maxEP = 0
        self.axe = 0
        self.dagger = 0
        self.unarmed = 0
        self.hammer = 0
        self.polearm = 0
        self.spear = 0
        self.staff = 0
        self.sword = 0
        self.archery = 0
        self.crossbow = 0
        self.sling = 0
        self.thrown = 0
        self.armor = 0
        self.dual_weapon = 0
        self.shield = 0
        self.bardic = 0
        self.conjuring = 0
        self.druidic = 0
        self.illusion = 0
        self.necromancy = 0
        self.sorcery = 0
        self.shamanic = 0
        self.spellcraft = 0
        self.summoning = 0
        self.focus = 0
        self.armorsmithing = 0
        self.tailoring = 0
        self.fletching = 0
        self.weaponsmithing = 0
        self.alchemy = 0
        self.lapidary = 0
        self.calligraphy = 0
        self.enchanting = 0
        self.herbalism = 0
        self.hunting = 0
        self.mining = 0
        self.bargaining = 0
        self.camping = 0
        self.first_aid = 0
        self.lore = 0
        self.pick_locks = 0
        self.scouting = 0
        self.search = 0
        self.stealth = 0
        self.traps = 0
        self.aeolandis = 0
        self.heiroform = 0
        self.high_gundis = 0
        self.old_praxic = 0
        self.praxic = 0
        self.runic = 0

    def create_in_database(self, ds):
        self.creation_date = time.strftime("%Y:%m:%d %H:%M:%S")
        self.cc_query = "INSERT INTO `characters` "\
            "(`id`,`account`,`name`,`creation_date`,"\
            "`race`,`gender`,`profession`,`strength`,`constitution`,"\
            "`intelligence`,`dexterity`,`level`,`hppl`,`mppl`,`currentHP`,"\
            "`maxHP`,`currentBP`,`maxBP`,`currentMP`,`maxMP`,`currentEP`,"\
            "`maxEP`,`axe`,`dagger`,`unarmed`,`hammer`,`polearm`,`spear`,"\
            "`staff`,`sword`,`archery`,`crossbow`,`sling`,`thrown`,`armor`,"\
            "`dual_weapon`,`shield`,`bardic`,`conjuring`,`druidic`,`illusion`,"\
            "`necromancy`,`sorcery`,`shamanic`,`summoning`,`spellcraft`,"\
            "`focus`,`armorsmithing`,`tailoring`,`fletching`,`weaponsmithing`,"\
            "`alchemy`,`lapidary`,`calligraphy`,`enchanting`,`herbalism`,"\
            "`hunting`,`mining`,`bargaining`,`camping`,`first_aid`,`lore`,"\
            "`pick_locks`,`scouting`,`search`,`stealth`,`traps`,`aeolandis`,"\
            "`heiroform`,`high_gundis`,`old_praxic`,`praxic`,`runic`) VALUES "\
            "(NULL,\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","\
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");" % ( self.account, \
            self.name, self.creation_date, self.race, self.gender, \
            self.profession, self.strength, self.constitution, \
            self.intelligence, self.dexterity, self.level, self.hppl, \
            self.mppl, self.currentHP, self.maxHP, self.currentBP, \
            self.maxBP, self.currentMP, self.maxMP, self.currentEP, \
            self.maxEP, self.axe, self.dagger, self.unarmed, self.hammer, \
            self.polearm, self.spear, self.staff, self.sword, self.archery, \
            self.crossbow, self.sling, self.thrown, self.armor, \
            self.dual_weapon, self.shield, self.bardic, self.conjuring, \
            self.druidic, self.illusion, self.necromancy, self.sorcery, \
            self.shamanic, self.summoning, self.spellcraft, self.focus, \
            self.armorsmithing, self.tailoring, self.fletching, \
            self.weaponsmithing, self.alchemy, self.lapidary, \
            self.calligraphy, self.enchanting, self.herbalism, self.hunting, \
            self.mining, self.bargaining, self.camping, self.first_aid, \
            self.lore, self.pick_locks, self.scouting, self.search, \
            self.stealth, self.traps, self.aeolandis, self.heiroform, \
            self.high_gundis, self.old_praxic, self.praxic, self.runic )
        ds.mysql_cursor.execute(self.cc_query)
        ds.database.commit()

    def calculate_max_condition(self):
        self.maxHP = (self.constitution * 10)
        self.maxBP = (self.constitution * 6)
        self.maxMP = (self.intelligence * 10)
        self.maxEP = (self.intelligence * 6)

    def calculate_start_stats(self):
        print "poop1"

    def calculate_start_attributes(self):
        print "poop2"

    def customize_character(self, ds):
        print "poop3"

def create_character(account):   
    proceed = 0
    t = Terminal()
    print t.bold_red("Welcome to the land of Oldentide.")
    print t.bold_green("You seem to be a stranger here...")
    while proceed == 0:
        new_name = raw_input( t.bold_green("What is your name? : ") )
        if query_character_exists(new_name):
            print t.bold_green("There already exists an individual with "\
                               "that name!")
            print t.bold_green("Please choose another.")
        elif ( len(new_name) < 3 or len(new_name) > 30 ):
            print t.bold_green("That can't possible be your real name, "\
                               "its the wrong length.")
            print t.bold_green("Please tell me the truth.")
        else:
            print (t.bold_green("So your name is %s, very well..." % new_name))
            proceed = 1
    proceed = 0
    while proceed == 0:
        new_gender = raw_input( t.bold_green("Are you male or female? : ") )
        if (( new_gender == "male" ) or ( new_gender == "Male" )):
            print t.bold_green("Ah excellent, the world is always in need "\
                               "of more good men like you!")
            proceed = 1
        elif (( new_gender == "female" ) or ( new_gender == "Female" )):
            print t.bold_green("Ah excellent, the world is always in need "\
                               "of more good women like you!")
            proceed = 1
        else:
            print "I didn't quite understand you..."
    print t.bold_green("Many different kinds of inhabitants walk the land "\
                       "of Oldentide.")
    print t.bold_green("The races of this world are ")
    with open("../text/races.txt", "r") as f:
        races_list = f.readlines()
    ccount = 0
    to_print = ''
    for r in races_list:
            r = r.rstrip()
            to_print += r
            to_print += "     "
    print to_print
    proceed = 0
    while proceed == 0:
        new_race = raw_input( t.bold_green("What race are you? : ") )
        if not new_race in races_list:
            print t.bold_green("I don't think I heard you right...")
        else:
            print ( t.bold_green("Ah I see, we welcome another %s to "\
                                 "Oldentide." % new_race ))
            proceed = 1
    print t.bold_green("Now surely you do not plan to walk this land without "\
                       "a purpose?")
    print t.bold_green("There are many professions that you may choose from, "\
                       "choose wisely!")
    with open("../text/professions.txt", "r") as f:
        profession_list = f.readlines()
    ccount = 0
    to_print = ''
    for p in profession_list:
        if ccount < 4:
            to_print.join("%s     " %p)
            ccount += 1
        elif ccount == 4:
            to_print.join("%s\n\r" %p)
            ccount = 0
    print to_print
    proceed = 0 
    while proceed == 0:
        print t.bold_green("What is your profession? : ")

def query_character_exists(new_name):
    return 0
