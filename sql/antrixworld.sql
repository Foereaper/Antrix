/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50624
Source Host           : localhost:3306
Source Database       : antrixworld

Target Server Type    : MYSQL
Target Server Version : 50624
File Encoding         : 65001

Date: 2015-07-01 00:56:48
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `accounts`
-- ----------------------------
DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `acct` int(30) NOT NULL AUTO_INCREMENT,
  `login` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `gm` varchar(50) NOT NULL,
  `flags` int(30) NOT NULL,
  `banned` int(30) NOT NULL,
  `lastlogin` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
  `lastip` varchar(50) NOT NULL,
  PRIMARY KEY (`acct`,`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of accounts
-- ----------------------------

-- ----------------------------
-- Table structure for `ai_agents`
-- ----------------------------
DROP TABLE IF EXISTS `ai_agents`;
CREATE TABLE `ai_agents` (
  `entryId` int(6) NOT NULL DEFAULT '0',
  `AI_AGENT` int(2) NOT NULL DEFAULT '0',
  `procEvent` int(2) NOT NULL DEFAULT '0',
  `procChance` int(3) NOT NULL DEFAULT '0',
  `procCount` int(6) NOT NULL DEFAULT '0',
  `spellId` int(6) NOT NULL DEFAULT '0',
  `spellType` int(2) NOT NULL DEFAULT '0',
  `spelltargetType` int(2) NOT NULL DEFAULT '0',
  `spellCooldown` int(8) NOT NULL DEFAULT '0',
  `floatMisc1` float NOT NULL DEFAULT '0',
  `Misc2` int(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entryId`,`AI_AGENT`,`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ai_agents
-- ----------------------------

-- ----------------------------
-- Table structure for `ai_threattospellid`
-- ----------------------------
DROP TABLE IF EXISTS `ai_threattospellid`;
CREATE TABLE `ai_threattospellid` (
  `spellId` int(5) NOT NULL DEFAULT '0',
  `mod` int(5) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ai_threattospellid
-- ----------------------------

-- ----------------------------
-- Table structure for `areatriggers`
-- ----------------------------
DROP TABLE IF EXISTS `areatriggers`;
CREATE TABLE `areatriggers` (
  `AreaTriggerid` bigint(20) NOT NULL DEFAULT '0',
  `Type` int(100) DEFAULT NULL,
  `Mapid` int(100) DEFAULT NULL,
  `Screen` int(100) DEFAULT NULL,
  `Name` varchar(100) DEFAULT '0',
  `x` float NOT NULL DEFAULT '0',
  `y` float NOT NULL DEFAULT '0',
  `z` float NOT NULL DEFAULT '0',
  `o` float NOT NULL DEFAULT '0',
  `required_honor_rank` int(5) NOT NULL,
  `required_level` int(5) NOT NULL,
  PRIMARY KEY (`AreaTriggerid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of areatriggers
-- ----------------------------
INSERT INTO `areatriggers` VALUES ('1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `auctionhouse`
-- ----------------------------
DROP TABLE IF EXISTS `auctionhouse`;
CREATE TABLE `auctionhouse` (
  `entryid` int(32) NOT NULL AUTO_INCREMENT,
  `auctioneer` bigint(64) unsigned NOT NULL DEFAULT '0',
  `AHid` int(32) NOT NULL DEFAULT '0',
  UNIQUE KEY `entryid` (`entryid`)
) ENGINE=MyISAM AUTO_INCREMENT=31 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of auctionhouse
-- ----------------------------

-- ----------------------------
-- Table structure for `auctions`
-- ----------------------------
DROP TABLE IF EXISTS `auctions`;
CREATE TABLE `auctions` (
  `auctionId` int(32) NOT NULL AUTO_INCREMENT,
  `auctionhouse` int(32) DEFAULT NULL,
  `item` bigint(10) DEFAULT NULL,
  `owner` bigint(10) DEFAULT NULL,
  `buyout` int(32) DEFAULT NULL,
  `time` int(32) DEFAULT NULL,
  `bidder` bigint(10) DEFAULT NULL,
  `bid` int(32) DEFAULT NULL,
  `deposit` int(32) DEFAULT NULL,
  PRIMARY KEY (`auctionId`)
) ENGINE=MyISAM AUTO_INCREMENT=37544 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of auctions
-- ----------------------------

-- ----------------------------
-- Table structure for `characters`
-- ----------------------------
DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `acct` int(20) unsigned NOT NULL DEFAULT '0',
  `name` varchar(21) NOT NULL DEFAULT '',
  `race` smallint(3) unsigned NOT NULL,
  `class` smallint(3) unsigned NOT NULL,
  `gender` tinyint(1) unsigned NOT NULL,
  `level` int(3) unsigned NOT NULL,
  `xp` int(30) unsigned NOT NULL,
  `exploration_data` longtext NOT NULL,
  `skills` longtext NOT NULL,
  `watched_faction_index` bigint(40) unsigned NOT NULL,
  `selected_pvp_title` int(30) unsigned NOT NULL,
  `available_pvp_titles` int(30) unsigned NOT NULL,
  `gold` int(30) unsigned NOT NULL,
  `ammo_id` int(30) unsigned NOT NULL,
  `available_prof_points` int(30) unsigned NOT NULL,
  `available_talent_points` int(30) unsigned NOT NULL,
  `current_hp` int(30) unsigned NOT NULL,
  `current_power` int(30) unsigned NOT NULL,
  `pvprank` int(30) unsigned NOT NULL,
  `bytes` int(30) unsigned NOT NULL,
  `bytes2` int(30) unsigned NOT NULL,
  `player_flags` int(30) unsigned NOT NULL,
  `player_bytes` int(30) unsigned NOT NULL,
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `mapId` int(8) unsigned NOT NULL DEFAULT '0',
  `zoneId` int(8) unsigned NOT NULL DEFAULT '0',
  `taximask` longtext NOT NULL,
  `banned` int(6) unsigned NOT NULL DEFAULT '0',
  `banReason` varchar(50) NOT NULL,
  `timestamp` text NOT NULL,
  `online` int(11) DEFAULT NULL,
  `bindpositionX` float NOT NULL DEFAULT '0',
  `bindpositionY` float NOT NULL DEFAULT '0',
  `bindpositionZ` float NOT NULL DEFAULT '0',
  `bindmapId` int(8) unsigned NOT NULL DEFAULT '0',
  `bindzoneId` int(8) unsigned NOT NULL DEFAULT '0',
  `isResting` int(1) NOT NULL DEFAULT '0',
  `restState` int(5) NOT NULL DEFAULT '0',
  `restTime` int(5) NOT NULL DEFAULT '0',
  `playedtime` longtext NOT NULL,
  `deathstate` int(2) NOT NULL DEFAULT '0',
  `TalentResetTimes` int(3) NOT NULL DEFAULT '0',
  `first_login` tinyint(1) NOT NULL DEFAULT '0',
  `forced_rename_pending` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `publicNote` varchar(32) NOT NULL DEFAULT '',
  `officerNote` varchar(32) NOT NULL DEFAULT '',
  `guildid` int(10) unsigned NOT NULL DEFAULT '0',
  `guildRank` int(10) unsigned NOT NULL DEFAULT '0',
  `charterId` int(10) NOT NULL,
  `totalstableslots` int(10) unsigned NOT NULL DEFAULT '0',
  `instance_id` int(10) NOT NULL DEFAULT '0',
  `entrypointmap` int(4) NOT NULL DEFAULT '0',
  `entrypointx` float NOT NULL DEFAULT '0',
  `entrypointy` float NOT NULL DEFAULT '0',
  `entrypointz` float NOT NULL DEFAULT '0',
  `entrypointo` float NOT NULL DEFAULT '0',
  `entrypointinstance` int(10) NOT NULL DEFAULT '0',
  `taxi_path` int(10) NOT NULL DEFAULT '0',
  `taxi_lastnode` int(10) NOT NULL DEFAULT '0',
  `taxi_mountid` int(10) NOT NULL DEFAULT '0',
  `transporter` int(10) NOT NULL DEFAULT '0',
  `transporter_xdiff` float NOT NULL DEFAULT '0',
  `transporter_ydiff` float NOT NULL DEFAULT '0',
  `transporter_zdiff` float NOT NULL DEFAULT '0',
  `spells` longtext NOT NULL,
  `deleted_spells` longtext NOT NULL,
  `reputation` longtext NOT NULL,
  `actions` longtext NOT NULL,
  `auras` longtext NOT NULL,
  `finished_quests` longtext NOT NULL,
  `lastDailyReset` int(30) NOT NULL,
  `killsToday` int(10) NOT NULL DEFAULT '0',
  `killsYesterday` int(10) NOT NULL DEFAULT '0',
  `killsLifeTime` int(10) NOT NULL DEFAULT '0',
  `honorToday` int(10) NOT NULL DEFAULT '0',
  `honorYesterday` int(10) NOT NULL DEFAULT '0',
  `honorPoints` int(10) NOT NULL DEFAULT '0',
  `difficulty` int(4) NOT NULL DEFAULT '0',
  UNIQUE KEY `guid` (`guid`),
  KEY `acct` (`acct`),
  KEY `guildid` (`guildid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of characters
-- ----------------------------

-- ----------------------------
-- Table structure for `charters`
-- ----------------------------
DROP TABLE IF EXISTS `charters`;
CREATE TABLE `charters` (
  `charterId` int(30) NOT NULL,
  `leaderGuid` int(20) unsigned NOT NULL DEFAULT '0',
  `guildName` varchar(32) NOT NULL DEFAULT '',
  `itemGuid` bigint(40) unsigned NOT NULL DEFAULT '0',
  `signer1` int(10) unsigned NOT NULL DEFAULT '0',
  `signer2` int(10) unsigned NOT NULL DEFAULT '0',
  `signer3` int(10) unsigned NOT NULL DEFAULT '0',
  `signer4` int(10) unsigned NOT NULL DEFAULT '0',
  `signer5` int(10) unsigned NOT NULL DEFAULT '0',
  `signer6` int(10) unsigned NOT NULL DEFAULT '0',
  `signer7` int(10) unsigned NOT NULL DEFAULT '0',
  `signer8` int(10) unsigned NOT NULL DEFAULT '0',
  `signer9` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`charterId`),
  UNIQUE KEY `leaderGuid` (`leaderGuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='InnoDB free: 11264 kB; InnoDB free: 18432 kB';

-- ----------------------------
-- Records of charters
-- ----------------------------

-- ----------------------------
-- Table structure for `clientaddons`
-- ----------------------------
DROP TABLE IF EXISTS `clientaddons`;
CREATE TABLE `clientaddons` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `crc` bigint(50) DEFAULT NULL,
  `banned` int(1) NOT NULL DEFAULT '0',
  `showinlist` int(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `index` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=153 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of clientaddons
-- ----------------------------

-- ----------------------------
-- Table structure for `command_overrides`
-- ----------------------------
DROP TABLE IF EXISTS `command_overrides`;
CREATE TABLE `command_overrides` (
  `command_name` varchar(100) NOT NULL,
  `access_level` varchar(10) NOT NULL,
  PRIMARY KEY (`command_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of command_overrides
-- ----------------------------

-- ----------------------------
-- Table structure for `corpses`
-- ----------------------------
DROP TABLE IF EXISTS `corpses`;
CREATE TABLE `corpses` (
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `zoneId` int(11) NOT NULL DEFAULT '38',
  `mapId` int(11) NOT NULL DEFAULT '0',
  `instanceId` int(11) NOT NULL DEFAULT '0',
  `data` longtext NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of corpses
-- ----------------------------

-- ----------------------------
-- Table structure for `creatureloot`
-- ----------------------------
DROP TABLE IF EXISTS `creatureloot`;
CREATE TABLE `creatureloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '25',
  `percentchance` float NOT NULL DEFAULT '100',
  PRIMARY KEY (`index`),
  KEY `i_creature_loot_creatureid` (`entryid`)
) ENGINE=MyISAM AUTO_INCREMENT=827980 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of creatureloot
-- ----------------------------

-- ----------------------------
-- Table structure for `creature_formations`
-- ----------------------------
DROP TABLE IF EXISTS `creature_formations`;
CREATE TABLE `creature_formations` (
  `creature_sqlid` int(30) NOT NULL,
  `followtarget_sqlid` int(30) NOT NULL,
  `follow_angle` float NOT NULL,
  `follow_dist` float NOT NULL,
  PRIMARY KEY (`creature_sqlid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of creature_formations
-- ----------------------------

-- ----------------------------
-- Table structure for `creature_names`
-- ----------------------------
DROP TABLE IF EXISTS `creature_names`;
CREATE TABLE `creature_names` (
  `entry` int(20) unsigned NOT NULL DEFAULT '0',
  `creature_name` varchar(100) NOT NULL DEFAULT '',
  `Subname` varchar(100) NOT NULL DEFAULT '',
  `Flags1` int(30) unsigned DEFAULT '0',
  `type` int(30) DEFAULT '0',
  `Family` int(30) DEFAULT '0',
  `Rank` int(30) DEFAULT '0',
  `unk4` int(30) DEFAULT '0',
  `SpellDataID` int(30) DEFAULT NULL,
  `displayid` int(30) DEFAULT '0',
  `unk2` float NOT NULL DEFAULT '1',
  `unk3` float NOT NULL DEFAULT '1',
  `Civilian` tinyint(30) DEFAULT NULL,
  `Leader` tinyint(30) DEFAULT NULL,
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of creature_names
-- ----------------------------
INSERT INTO `creature_names` VALUES ('1', 'test', 'test', '0', '0', '0', '0', '0', null, '1', '1', '1', null, null);

-- ----------------------------
-- Table structure for `creature_proto`
-- ----------------------------
DROP TABLE IF EXISTS `creature_proto`;
CREATE TABLE `creature_proto` (
  `entry` int(30) unsigned NOT NULL,
  `level` int(30) unsigned NOT NULL,
  `faction` int(30) unsigned NOT NULL,
  `health` int(30) unsigned NOT NULL,
  `mana` int(30) unsigned NOT NULL,
  `scale` float NOT NULL,
  `npcflags` int(30) unsigned NOT NULL,
  `attacktime` int(30) unsigned NOT NULL,
  `mindamage` float NOT NULL,
  `maxdamage` float NOT NULL,
  `rangedattacktime` int(30) unsigned NOT NULL,
  `rangedmindamage` float unsigned NOT NULL,
  `rangedmaxdamage` float unsigned NOT NULL,
  `mountdisplayid` int(30) unsigned NOT NULL,
  `item1slotdisplay` int(30) unsigned NOT NULL,
  `item1info1` int(30) unsigned NOT NULL,
  `item1info2` int(30) unsigned NOT NULL,
  `item2slotdisplay` int(30) unsigned NOT NULL,
  `item2info1` int(30) unsigned NOT NULL,
  `item2info2` int(30) unsigned NOT NULL,
  `item3slotdisplay` int(30) unsigned NOT NULL,
  `item3info1` int(30) unsigned NOT NULL,
  `item3info2` int(30) unsigned NOT NULL,
  `respawntime` int(30) unsigned NOT NULL,
  `resistance0_armor` int(30) unsigned NOT NULL,
  `resistance1` int(30) unsigned NOT NULL,
  `resistance2` int(30) unsigned NOT NULL,
  `resistance3` int(30) unsigned NOT NULL,
  `resistance4` int(30) unsigned NOT NULL,
  `resistance5` int(30) unsigned NOT NULL,
  `resistance6` int(30) unsigned NOT NULL,
  `combat_reach` float NOT NULL,
  `bounding_radius` float NOT NULL,
  `auras` longtext NOT NULL,
  `boss` int(11) unsigned NOT NULL,
  `money` int(6) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `ID` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of creature_proto
-- ----------------------------
INSERT INTO `creature_proto` VALUES ('1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0');

-- ----------------------------
-- Table structure for `creature_quest_finisher`
-- ----------------------------
DROP TABLE IF EXISTS `creature_quest_finisher`;
CREATE TABLE `creature_quest_finisher` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of creature_quest_finisher
-- ----------------------------

-- ----------------------------
-- Table structure for `creature_quest_starter`
-- ----------------------------
DROP TABLE IF EXISTS `creature_quest_starter`;
CREATE TABLE `creature_quest_starter` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of creature_quest_starter
-- ----------------------------

-- ----------------------------
-- Table structure for `creature_spawns`
-- ----------------------------
DROP TABLE IF EXISTS `creature_spawns`;
CREATE TABLE `creature_spawns` (
  `id` int(30) unsigned NOT NULL,
  `entry` int(30) NOT NULL,
  `Map` int(30) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `o` float NOT NULL,
  `movetype` int(30) NOT NULL,
  `displayid` int(30) unsigned NOT NULL,
  `factionid` int(30) NOT NULL,
  `flags` int(30) NOT NULL,
  `bytes` int(30) unsigned NOT NULL,
  `bytes2` int(30) unsigned NOT NULL,
  `emote_state` int(30) NOT NULL,
  `npc_respawn_link` int(30) NOT NULL DEFAULT '0',
  UNIQUE KEY `id` (`id`),
  KEY `map` (`Map`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of creature_spawns
-- ----------------------------

-- ----------------------------
-- Table structure for `creature_waypoints`
-- ----------------------------
DROP TABLE IF EXISTS `creature_waypoints`;
CREATE TABLE `creature_waypoints` (
  `creatureid` int(10) NOT NULL DEFAULT '0',
  `waypointid` int(2) NOT NULL DEFAULT '0',
  `x` float NOT NULL DEFAULT '0',
  `y` float NOT NULL DEFAULT '0',
  `z` float NOT NULL DEFAULT '0',
  `waittime` int(6) NOT NULL DEFAULT '0',
  `flags` int(3) NOT NULL DEFAULT '0',
  `forwardemoteoneshot` int(1) NOT NULL DEFAULT '0',
  `forwardemoteid` int(4) NOT NULL DEFAULT '0',
  `backwardemoteoneshot` int(1) NOT NULL DEFAULT '0',
  `backwardemoteid` int(4) NOT NULL DEFAULT '0',
  `forwardskinid` int(10) NOT NULL DEFAULT '0',
  `backwardskinid` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`creatureid`,`waypointid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of creature_waypoints
-- ----------------------------

-- ----------------------------
-- Table structure for `fishing`
-- ----------------------------
DROP TABLE IF EXISTS `fishing`;
CREATE TABLE `fishing` (
  `Zone` int(11) unsigned NOT NULL DEFAULT '0',
  `MinSkill` int(11) unsigned DEFAULT NULL,
  `MaxSkill` int(11) unsigned DEFAULT NULL,
  UNIQUE KEY `Zone` (`Zone`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of fishing
-- ----------------------------
INSERT INTO `fishing` VALUES ('1', '1', '1');

-- ----------------------------
-- Table structure for `fishingloot`
-- ----------------------------
DROP TABLE IF EXISTS `fishingloot`;
CREATE TABLE `fishingloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(10) unsigned NOT NULL DEFAULT '0',
  `itemid` int(10) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`)
) ENGINE=MyISAM AUTO_INCREMENT=2275 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of fishingloot
-- ----------------------------

-- ----------------------------
-- Table structure for `gameobject_names`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_names`;
CREATE TABLE `gameobject_names` (
  `entry` int(20) unsigned NOT NULL DEFAULT '0',
  `Type` int(100) unsigned NOT NULL DEFAULT '0',
  `DisplayID` int(100) unsigned NOT NULL DEFAULT '0',
  `Name` varchar(100) NOT NULL DEFAULT '0',
  `sound0` int(30) NOT NULL DEFAULT '0',
  `sound1` int(30) NOT NULL DEFAULT '0',
  `sound2` int(30) NOT NULL DEFAULT '0',
  `sound3` int(30) NOT NULL DEFAULT '0',
  `sound4` int(30) NOT NULL DEFAULT '0',
  `sound5` int(30) NOT NULL DEFAULT '0',
  `sound6` int(30) NOT NULL DEFAULT '0',
  `sound7` int(30) NOT NULL DEFAULT '0',
  `sound8` int(30) NOT NULL DEFAULT '0',
  `sound9` int(30) NOT NULL DEFAULT '0',
  `unknown1` int(30) NOT NULL DEFAULT '0',
  `unknown2` int(30) NOT NULL DEFAULT '0',
  `unknown3` int(30) NOT NULL DEFAULT '0',
  `unknown4` int(30) NOT NULL DEFAULT '0',
  `unknown5` int(30) NOT NULL DEFAULT '0',
  `unknown6` int(30) NOT NULL DEFAULT '0',
  `unknown7` int(30) NOT NULL DEFAULT '0',
  `unknown8` int(30) NOT NULL DEFAULT '0',
  `unknown9` int(30) NOT NULL DEFAULT '0',
  `unknown10` int(30) NOT NULL DEFAULT '0',
  `unknown11` int(30) NOT NULL DEFAULT '0',
  `unknown12` int(30) NOT NULL DEFAULT '0',
  `unknown13` int(30) NOT NULL DEFAULT '0',
  `unknown14` int(30) NOT NULL DEFAULT '0',
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of gameobject_names
-- ----------------------------
INSERT INTO `gameobject_names` VALUES ('1', '1', '1', 'test', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `gameobject_quest_finisher`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_quest_finisher`;
CREATE TABLE `gameobject_quest_finisher` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of gameobject_quest_finisher
-- ----------------------------

-- ----------------------------
-- Table structure for `gameobject_quest_item_binding`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_quest_item_binding`;
CREATE TABLE `gameobject_quest_item_binding` (
  `gameobject_entry` int(11) NOT NULL DEFAULT '0',
  `quest_id` int(11) NOT NULL DEFAULT '0',
  `item_id` int(11) NOT NULL DEFAULT '0',
  `item_count` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of gameobject_quest_item_binding
-- ----------------------------

-- ----------------------------
-- Table structure for `gameobject_quest_pickup_binding`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_quest_pickup_binding`;
CREATE TABLE `gameobject_quest_pickup_binding` (
  `gameobject_entry` int(11) NOT NULL DEFAULT '0',
  `quest_id` int(11) NOT NULL DEFAULT '0',
  `required_count` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of gameobject_quest_pickup_binding
-- ----------------------------

-- ----------------------------
-- Table structure for `gameobject_quest_starter`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_quest_starter`;
CREATE TABLE `gameobject_quest_starter` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `quest` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`quest`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of gameobject_quest_starter
-- ----------------------------

-- ----------------------------
-- Table structure for `gameobject_spawns`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_spawns`;
CREATE TABLE `gameobject_spawns` (
  `ID` int(30) unsigned NOT NULL,
  `Entry` int(10) unsigned NOT NULL DEFAULT '0',
  `Map` int(10) unsigned NOT NULL DEFAULT '0',
  `x` float NOT NULL DEFAULT '0',
  `y` float NOT NULL DEFAULT '0',
  `z` float NOT NULL DEFAULT '0',
  `Facing` float NOT NULL DEFAULT '0',
  `o1` float NOT NULL DEFAULT '0',
  `o2` float NOT NULL DEFAULT '0',
  `o3` float NOT NULL DEFAULT '0',
  `o4` float NOT NULL DEFAULT '0',
  `State` int(10) unsigned NOT NULL DEFAULT '0',
  `Flags` int(10) unsigned NOT NULL DEFAULT '0',
  `Faction` int(10) unsigned NOT NULL DEFAULT '0',
  `Scale` float NOT NULL DEFAULT '0',
  `state_npc_link` int(30) NOT NULL,
  UNIQUE KEY `ID` (`ID`),
  KEY `Map` (`Map`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251 COLLATE=cp1251_general_cs;

-- ----------------------------
-- Records of gameobject_spawns
-- ----------------------------

-- ----------------------------
-- Table structure for `gm_tickets`
-- ----------------------------
DROP TABLE IF EXISTS `gm_tickets`;
CREATE TABLE `gm_tickets` (
  `guid` int(6) NOT NULL DEFAULT '0',
  `name` varchar(200) NOT NULL DEFAULT '',
  `level` int(6) NOT NULL DEFAULT '0',
  `type` int(2) NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `message` text NOT NULL,
  `timestamp` text,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of gm_tickets
-- ----------------------------

-- ----------------------------
-- Table structure for `graveyards`
-- ----------------------------
DROP TABLE IF EXISTS `graveyards`;
CREATE TABLE `graveyards` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `o` float NOT NULL,
  `zoneid` int(10) NOT NULL DEFAULT '0',
  `adjacentzoneid` int(10) NOT NULL DEFAULT '0',
  `mapid` int(10) NOT NULL DEFAULT '0',
  `factionid` int(10) NOT NULL DEFAULT '0',
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=386 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of graveyards
-- ----------------------------
INSERT INTO `graveyards` VALUES ('1', '-9115', '423', '93.6419', '4.0817', '12', '1519', '0', '3', 'Elwynn Forest');
INSERT INTO `graveyards` VALUES ('2', '-9271', '-2305', '69.5811', '4.0817', '44', '0', '0', '3', 'Lakeshire');
INSERT INTO `graveyards` VALUES ('3', '-10774.3', '-1189.67', '32.9692', '4.0817', '10', '0', '0', '3', 'Darkshire');
INSERT INTO `graveyards` VALUES ('4', '-10546.9', '1197.24', '31.7101', '4.0817', '40', '0', '0', '3', 'Sentinel Hill');
INSERT INTO `graveyards` VALUES ('5', '-5687', '-515', '396.274', '4.0817', '1', '1537', '0', '3', 'Kharanos');
INSERT INTO `graveyards` VALUES ('6', '-5351.23', '-2881.58', '341.031', '4.0817', '38', '0', '0', '3', 'Loch Modan');
INSERT INTO `graveyards` VALUES ('7', '-3289.12', '-2435.99', '18.5966', '4.0817', '11', '0', '0', '3', 'Wetlands');
INSERT INTO `graveyards` VALUES ('8', '-6289.91', '-3493.11', '251.339', '4.0817', '3', '0', '0', '3', 'Badlands');
INSERT INTO `graveyards` VALUES ('9', '-592.601', '-2523.49', '91.8176', '4.0817', '17', '0', '1', '3', 'The Barrens');
INSERT INTO `graveyards` VALUES ('10', '-1443.49', '1973.37', '85.5681', '4.0817', '405', '0', '1', '3', 'Kodo Graveyard');
INSERT INTO `graveyards` VALUES ('11', '233.458', '-4793.73', '10.1905', '4.0817', '14', '1637', '1', '3', 'Razor Hill');
INSERT INTO `graveyards` VALUES ('12', '1357.1', '-4412.01', '28.4431', '4.0817', '14', '1637', '1', '3', 'Durotar');
INSERT INTO `graveyards` VALUES ('13', '-2944.56', '-153.215', '65.8427', '4.0817', '215', '0', '1', '3', 'Red Cloud Mesa');
INSERT INTO `graveyards` VALUES ('14', '6739.19', '209.993', '23.3211', '4.0817', '148', '0', '1', '3', 'Darkshore');
INSERT INTO `graveyards` VALUES ('15', '-11110.4', '-1833.24', '71.8642', '4.0817', '41', '0', '0', '3', 'Morgan s Plot');
INSERT INTO `graveyards` VALUES ('16', '-4656', '-1765', '-41.2877', '4.0817', '400', '0', '1', '3', 'Thousand Needles');
INSERT INTO `graveyards` VALUES ('17', '-6432.26', '-278.292', '3.78629', '4.0817', '1377', '0', '1', '3', 'Valor s Rest');
INSERT INTO `graveyards` VALUES ('18', '-2175.19', '-342.027', '-5.37017', '4.0817', '215', '0', '1', '3', 'Bloodhoof Village');
INSERT INTO `graveyards` VALUES ('19', '10054.3', '2117.12', '1329.8', '4.0817', '1657', '0', '1', '3', 'Darnassus');
INSERT INTO `graveyards` VALUES ('20', '9701.25', '945.62', '1291.39', '4.0817', '141', '1657', '1', '3', 'Dolanaar');
INSERT INTO `graveyards` VALUES ('21', '2633.41', '-629.735', '107.577', '4.0817', '331', '0', '1', '3', 'Astranaar');
INSERT INTO `graveyards` VALUES ('22', '10384.8', '811.531', '1317.54', '4.0817', '141', '1657', '1', '3', 'Aldrassil');
INSERT INTO `graveyards` VALUES ('23', '1882.94', '1629.11', '94.3531', '4.0817', '85', '1497', '0', '3', 'Deathknell');
INSERT INTO `graveyards` VALUES ('24', '1822.61', '214.674', '59.7544', '4.0817', '85', '1497', '0', '3', 'Ruins of Lordaeron');
INSERT INTO `graveyards` VALUES ('25', '516.194', '1589.81', '127.399', '4.0817', '130', '0', '0', '3', 'The Sepulcher');
INSERT INTO `graveyards` VALUES ('26', '-18.6777', '-981.171', '55.8377', '4.0817', '267', '0', '0', '3', 'Tarren Mill');
INSERT INTO `graveyards` VALUES ('27', '-1472.29', '-2617.96', '49.2121', '4.0817', '45', '0', '0', '3', 'Arathi Highlands');
INSERT INTO `graveyards` VALUES ('28', '-6164.23', '336.321', '399.742', '4.0817', '1', '1537', '0', '3', 'Coldridge Valley');
INSERT INTO `graveyards` VALUES ('29', '-5680.04', '-518.92', '396.274', '40817', '1', '1537', '0', '3', 'Kharanos');
INSERT INTO `graveyards` VALUES ('30', '-5049.45', '-809.697', '495.127', '4.0817', '1', '1537', '0', '3', 'Gates of Ironforge');
INSERT INTO `graveyards` VALUES ('31', '-6805', '-2287.19', '280.752', '4.0817', '3', '0', '0', '3', 'Badlands');
INSERT INTO `graveyards` VALUES ('32', '-9403.25', '-2037.69', '58.3634', '4.0817', '44', '0', '0', '3', 'Redridge Mountains');
INSERT INTO `graveyards` VALUES ('33', '-8935.33', '-188.646', '80.2796', '4.0817', '12', '1519', '0', '3', 'Northshire Valley');
INSERT INTO `graveyards` VALUES ('34', '-9339.46', '171.408', '61.5637', '4.0817', '12', '1519', '0', '3', 'Elwynn Forest');
INSERT INTO `graveyards` VALUES ('35', '-9151.98', '410.944', '93.1324', '4.0817', '12', '1519', '0', '3', 'Elwynn Forest');
INSERT INTO `graveyards` VALUES ('36', '-10567.8', '-3377.2', '22.2576', '4.0817', '8', '0', '0', '3', 'Stonard');
INSERT INTO `graveyards` VALUES ('37', '-14285', '288.447', '32.3193', '4.0817', '33', '0', '0', '3', 'The Cape of Stranglethorn');
INSERT INTO `graveyards` VALUES ('38', '8706', '965', '12.6923', '4.0817', '141', '0', '1', '3', 'Rut theran Village');
INSERT INTO `graveyards` VALUES ('39', '-732.799', '-592.502', '22.8785', '4.0817', '267', '0', '0', '3', 'Southshore');
INSERT INTO `graveyards` VALUES ('40', '-3525.71', '-4315.46', '6.98795', '4.0817', '15', '0', '1', '3', 'Dustwallow Marsh');
INSERT INTO `graveyards` VALUES ('41', '-7190.95', '-3944.65', '9.20883', '4.0817', '440', '0', '1', '3', 'Gadgetzan');
INSERT INTO `graveyards` VALUES ('42', '-2517.75', '-1972.64', '91.7849', '4.0817', '17', '0', '1', '3', 'Southern Barrens');
INSERT INTO `graveyards` VALUES ('43', '-1081.4', '-3478.68', '63.6295', '4.0817', '17', '0', '1', '3', 'Ratchet');
INSERT INTO `graveyards` VALUES ('44', '2348.67', '492.027', '33.3693', '4.0817', '85', '1497', '0', '3', 'Brill');
INSERT INTO `graveyards` VALUES ('45', '-4596.4', '3229.43', '8.97498', '4.0817', '357', '0', '1', '3', 'Feathermoon Stronghold');
INSERT INTO `graveyards` VALUES ('46', '-4439.97', '370.153', '51.3567', '4.0817', '357', '0', '1', '3', 'Camp Mojache');
INSERT INTO `graveyards` VALUES ('47', '-5530.28', '-3459.28', '-45.7628', '4.0817', '400', '0', '1', '3', 'Thousand Needles');
INSERT INTO `graveyards` VALUES ('48', '323.513', '-2227.2', '137.771', '4.0817', '47', '0', '0', '3', 'Aerie Peak');
INSERT INTO `graveyards` VALUES ('49', '2681.06', '-4009.75', '107.833', '4.0817', '16', '0', '1', '3', 'Azshara');
INSERT INTO `graveyards` VALUES ('50', '-10846.6', '-2949.49', '13.245', '4.0817', '4', '0', '0', '3', 'Dreadmaul Hold');
INSERT INTO `graveyards` VALUES ('51', '-11542.6', '-228.637', '27.8548', '4.0817', '33', '0', '0', '3', 'Stranglethorn Vale');
INSERT INTO `graveyards` VALUES ('52', '898.261', '434.53', '65.792', '4.0817', '406', '0', '1', '3', 'Webwinder Path');
INSERT INTO `graveyards` VALUES ('53', '2604.52', '-543.39', '88.9996', '4.0817', '85', '1497', '0', '3', 'Faol s Rest');
INSERT INTO `graveyards` VALUES ('54', '3806.54', '-1600.29', '218.813', '4.0817', '361', '0', '1', '3', 'Morlos Aran');
INSERT INTO `graveyards` VALUES ('55', '-7205.56', '-2436.67', '-218.156', '4.0817', '490', '0', '1', '3', 'The Marshlands');
INSERT INTO `graveyards` VALUES ('56', '4291.28', '96.9557', '42.9213', '4.0817', '148', '0', '1', '3', 'Twilight Vale');
INSERT INTO `graveyards` VALUES ('57', '-3347.72', '-856.713', '1.05959', '4.0817', '11', '0', '0', '3', 'Baradin Bay');
INSERT INTO `graveyards` VALUES ('58', '908.323', '-1520.29', '55.0371', '4.0817', '28', '0', '0', '3', 'Chillwind Camp');
INSERT INTO `graveyards` VALUES ('59', '2116.79', '-5287.34', '81.2067', '4.0817', '139', '0', '0', '3', 'Light s Hope Chapel');
INSERT INTO `graveyards` VALUES ('60', '6875.76', '-4661.54', '701.036', '4.0817', '618', '0', '1', '3', 'Everlook');
INSERT INTO `graveyards` VALUES ('61', '2421.72', '-2953.62', '123.472', '4.0817', '331', '0', '1', '3', 'Nightsong Woods');
INSERT INTO `graveyards` VALUES ('62', '1750.34', '-669.79', '44.5185', '4.0817', '85', '1497', '0', '3', 'The Bulwark');
INSERT INTO `graveyards` VALUES ('63', '16310.3', '16268.9', '19.2292', '4.0817', '876', '0', '1', '3', 'GM Island');
INSERT INTO `graveyards` VALUES ('64', '2942.76', '-6037.13', '4.01579', '4.0817', '16', '0', '1', '3', 'Southridge Beach');
INSERT INTO `graveyards` VALUES ('65', '908.323', '-1520.29', '55.0371', '4.0817', '28', '0', '0', '3', 'Chillwind Camp');
INSERT INTO `graveyards` VALUES ('66', '4788.78', '-6845', '89.7527', '4.0817', '16', '0', '1', '3', 'Legash Encampment');
INSERT INTO `graveyards` VALUES ('67', '-3127.69', '-3046.94', '33.7892', '4.0817', '15', '0', '1', '3', 'Dustwallow Marsh');
INSERT INTO `graveyards` VALUES ('68', '-7490.45', '-2132.62', '142.471', '4.0817', '46', '51', '0', '3', 'Flame Crest');
INSERT INTO `graveyards` VALUES ('69', '7426', '-2809', '463.894', '4.0817', '493', '0', '1', '3', 'Moonglade');
INSERT INTO `graveyards` VALUES ('70', '1392', '-3701', '76.8411', '4.0817', '139', '0', '0', '3', 'Darrowshire');
INSERT INTO `graveyards` VALUES ('71', '5935.47', '-1217.75', '383.22', '4.0817', '361', '0', '1', '3', 'Irontree Woods');
INSERT INTO `graveyards` VALUES ('72', '-6450.61', '-1113.51', '308.162', '4.0817', '51', '0', '0', '3', 'Thorium Point');
INSERT INTO `graveyards` VALUES ('73', '-778', '-4985', '19.0062', '4.0817', '14', '1637', '1', '3', 'Sen jin Village');
INSERT INTO `graveyards` VALUES ('74', '-634.635', '-4296.03', '40.5153', '4.0817', '14', '1637', '1', '3', 'Valley of Trials');
INSERT INTO `graveyards` VALUES ('75', '-291', '-4374', '106.59', '4.0817', '47', '0', '0', '3', 'The Overlook Cliffs');
INSERT INTO `graveyards` VALUES ('76', '1035.27', '-2104.28', '122.945', '4.0817', '17', '0', '1', '3', 'Mor shan Base Camp');
INSERT INTO `graveyards` VALUES ('77', '1459.17', '-1858.67', '124.448', '4.0817', '331', '0', '1', '3', 'Silverwing Grove');
INSERT INTO `graveyards` VALUES ('78', '101.144', '-184.934', '192.697', '4.0817', '36', '0', '0', '3', 'Growless Cave');
INSERT INTO `graveyards` VALUES ('79', '536.495', '-1085.72', '149.545', '4.0817', '36', '0', '0', '3', 'Alterac Mountains');
INSERT INTO `graveyards` VALUES ('80', '-4590.41', '1632.08', '93.9638', '4.0817', '357', '0', '1', '3', 'Dire Maul');
INSERT INTO `graveyards` VALUES ('81', '1177.78', '-4464.24', '21.3597', '4.0817', '14', '1637', '1', '3', 'Durotar');
INSERT INTO `graveyards` VALUES ('82', '-981.917', '-74.6465', '20.4909', '4.0817', '1638', '0', '1', '3', 'Thunder Bluff');
INSERT INTO `graveyards` VALUES ('83', '-5165.52', '-874.664', '507.142', '4.0817', '1', '1537', '0', '3', 'Gates of Ironforge');
INSERT INTO `graveyards` VALUES ('84', '1780.11', '221.761', '59.3442', '4.0817', '85', '1497', '0', '3', 'Ruins of Lordaeron');
INSERT INTO `graveyards` VALUES ('85', '-9552.46', '-1374.05', '51.2978', '4.0817', '12', '1519', '0', '3', 'Eastvale Logging Camp');
INSERT INTO `graveyards` VALUES ('86', '1236.89', '-2411.99', '60.7066', '4.0817', '28', '0', '0', '3', 'Caer Darrow');
INSERT INTO `graveyards` VALUES ('87', '-831.881', '-3518.52', '72.5374', '4.0817', '45', '0', '0', '3', 'Hammerfall');
INSERT INTO `graveyards` VALUES ('88', '-1215.59', '-2531.75', '21.6381', '4.0817', '45', '0', '0', '3', 'Refuge Pointe');
INSERT INTO `graveyards` VALUES ('89', '2647.55', '-4014.39', '105.904', '4.0817', '139', '0', '0', '3', 'Blackwood Lake');
INSERT INTO `graveyards` VALUES ('90', '-6831.32', '891.437', '33.7702', '4.0817', '1377', '0', '1', '3', 'Cenarion Hold');
INSERT INTO `graveyards` VALUES ('91', '-10606.8', '294.048', '31.8466', '4.0817', '10', '0', '0', '3', 'Raven Hill');
INSERT INTO `graveyards` VALUES ('92', '10458.5', '-6364.61', '39.7907', '4.0817', '3430', '3487', '530', '3', 'Sunstrider Isle');
INSERT INTO `graveyards` VALUES ('93', '-7991.57', '1557.8', '5.01986', '4.0817', '1377', '0', '1', '3', 'The Scarab Wall');
INSERT INTO `graveyards` VALUES ('94', '8936.56', '-7439.9', '8.3249', '4.0817', '3430', '3487', '530', '3', 'Farstrider Retreat');
INSERT INTO `graveyards` VALUES ('95', '7694.18', '-6730.11', '48.5174', '4.0817', '3433', '0', '530', '3', 'Ghostlands');
INSERT INTO `graveyards` VALUES ('96', '7015.23', '-7300', '45.2103', '4.0817', '3433', '0', '530', '3', 'Ghostlands');
INSERT INTO `graveyards` VALUES ('97', '6730.49', '-7936.89', '150.245', '4.0817', '3433', '0', '530', '3', 'Ghostlands');
INSERT INTO `graveyards` VALUES ('98', '-4123.14', '-13660.1', '74.581', '4.0817', '3524', '3557', '530', '3', 'Ammen Vale');
INSERT INTO `graveyards` VALUES ('99', '158.06', '2562.73', '76.3447', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('100', '-803.012', '2702.59', '106.687', '4.0817', '3483', '0', '530', '3', 'Honor Hold');
INSERT INTO `graveyards` VALUES ('101', '9500', '-6966.66', '18.1827', '4.0817', '3430', '3487', '530', '3', 'The Dead Scar');
INSERT INTO `graveyards` VALUES ('102', '8709.46', '-6671.76', '70.336', '4.0817', '3430', '3487', '530', '3', 'Fairbreeze Village');
INSERT INTO `graveyards` VALUES ('103', '-4312.78', '-12441', '17.1672', '4.0817', '3524', '3557', '530', '3', 'Azuremyst Isle');
INSERT INTO `graveyards` VALUES ('104', '-3324.31', '-12089.9', '28.2816', '4.0817', '3524', '3557', '530', '3', 'Azuremyst Isle');
INSERT INTO `graveyards` VALUES ('105', '-2020.59', '-11983.5', '32.5854', '4.0817', '3525', '0', '530', '3', 'Bloodmyst Isle');
INSERT INTO `graveyards` VALUES ('106', '-1754.21', '-11067.3', '76.3371', '4.0817', '3525', '0', '530', '3', 'Vindicator s Rest');
INSERT INTO `graveyards` VALUES ('107', '1978.47', '-3655.89', '119.786', '4.0817', '139', '0', '0', '3', 'Eastern Plaguelands');
INSERT INTO `graveyards` VALUES ('108', '335.886', '7625.12', '22.7737', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('109', '-2499.9', '6812.86', '22.0149', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('110', '181.475', '4361.58', '116.929', '4.0817', '3483', '0', '530', '3', 'Temple of Telhamat');
INSERT INTO `graveyards` VALUES ('111', '-695.875', '4118.21', '63.0812', '4.0817', '3483', '0', '530', '3', 'Falcon Watch');
INSERT INTO `graveyards` VALUES ('112', '742.628', '2887.71', '8.74075', '4.0817', '3483', '0', '530', '3', 'Stonescythe Canyon');
INSERT INTO `graveyards` VALUES ('113', '101.144', '-184.934', '192.697', '4.0817', '36', '0', '0', '3', 'Growless Cave');
INSERT INTO `graveyards` VALUES ('114', '540.31', '3932.88', '175.219', '4.0817', '3483', '0', '530', '3', 'Mag har Post');
INSERT INTO `graveyards` VALUES ('115', '540.98', '3144.23', '9.01128', '4.0817', '3483', '0', '530', '3', 'Stonescythe Canyon');
INSERT INTO `graveyards` VALUES ('116', '582.864', '2954.06', '5.63896', '4.0817', '3483', '0', '530', '3', 'Stonescythe Canyon');
INSERT INTO `graveyards` VALUES ('117', '742.628', '2887.71', '8.74075', '4.0817', '3483', '0', '530', '3', 'Stonescythe Canyon');
INSERT INTO `graveyards` VALUES ('118', '1148.44', '1798.14', '115.928', '4.0817', '3483', '0', '530', '3', 'The Abyssal Shelf');
INSERT INTO `graveyards` VALUES ('119', '851.694', '1688.06', '89.7413', '4.0817', '3483', '0', '530', '3', 'The Abyssal Shelf');
INSERT INTO `graveyards` VALUES ('120', '608.097', '1778.63', '103.861', '4.0817', '3483', '0', '530', '3', 'The Abyssal Shelf');
INSERT INTO `graveyards` VALUES ('121', '354.618', '1952.75', '24.0142', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('122', '107.712', '1841.23', '21.6667', '4.0817', '3483', '0', '530', '3', 'The Legion Front');
INSERT INTO `graveyards` VALUES ('123', '274.599', '1674.63', '-5.50907', '4.0817', '3483', '0', '530', '3', 'The Legion Front');
INSERT INTO `graveyards` VALUES ('124', '60.881', '1542.69', '17.2558', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('125', '-92.8317', '1350.91', '-12.6829', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('126', '134.528', '1230.39', '2.46611', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('127', '298.666', '1225.23', '-1.37024', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('128', '386.682', '1044.78', '26.3317', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('129', '337.84', '853.218', '13.813', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('130', '60.3844', '725.155', '14.8662', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('131', '-213.512', '730.684', '-1.21942', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('132', '-570.327', '675.785', '-0.81186', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('133', '-958.584', '803.907', '1.95012', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('134', '-827.569', '1194.34', '16.1594', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('135', '-465.075', '1272.1', '12.4109', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('136', '-668.975', '1516.19', '18.0938', '4.0817', '3483', '0', '530', '3', 'Void Ridge');
INSERT INTO `graveyards` VALUES ('137', '-1278.37', '1381.71', '9.43431', '4.0817', '3483', '0', '530', '3', 'Void Ridge');
INSERT INTO `graveyards` VALUES ('138', '-1306.28', '2478.4', '57.0979', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('139', '-1497.4', '2657.17', '-53.356', '4.0817', '3483', '0', '530', '3', 'Expedition Armory');
INSERT INTO `graveyards` VALUES ('140', '-1445.7', '3050.23', '-16.3693', '4.0817', '3483', '0', '530', '3', 'The Warp Fields');
INSERT INTO `graveyards` VALUES ('141', '-1510.36', '3281.81', '-16.5862', '4.0817', '3483', '0', '530', '3', 'The Warp Fields');
INSERT INTO `graveyards` VALUES ('142', '248.339', '7084.93', '36.6211', '4.0817', '3521', '0', '530', '3', 'Twin Spire Ruins');
INSERT INTO `graveyards` VALUES ('143', '211.315', '6200.03', '22.3586', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('144', '1286.73', '7883.12', '10.5754', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('145', '-212.452', '5579.67', '22.2861', '4.0817', '3521', '0', '530', '3', 'Cenarion Refuge');
INSERT INTO `graveyards` VALUES ('146', '1011.16', '5039.57', '-27.2596', '4.0817', '3521', '0', '530', '3', 'The Dead Mire');
INSERT INTO `graveyards` VALUES ('147', '781.713', '4987.82', '-12.2221', '4.0817', '3521', '0', '530', '3', 'The Dead Mire');
INSERT INTO `graveyards` VALUES ('148', '1001.9', '5714.57', '-9.33086', '4.0817', '3521', '0', '530', '3', 'The Dead Mire');
INSERT INTO `graveyards` VALUES ('149', '1394.98', '7756.5', '11.8316', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('150', '1412.41', '8430.12', '-4.31167', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('151', '1398.58', '7763.03', '8.27597', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('152', '1317.5', '8135.39', '-3.34051', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('153', '1706.28', '8407.81', '-24.7207', '4.0817', '3521', '0', '530', '3', 'Ango rosh Stronghold');
INSERT INTO `graveyards` VALUES ('154', '1348.2', '8677.57', '6.73334', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('155', '1838.93', '8496.51', '-19.2404', '4.0817', '3521', '0', '530', '3', 'Ango rosh Stronghold');
INSERT INTO `graveyards` VALUES ('156', '1347.02', '8679.23', '6.5805', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('157', '1104.4', '8781.98', '-10.9985', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('158', '747.447', '8702.9', '6.19002', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('159', '381.31', '9113.74', '-4.32158', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('160', '702.758', '8927.53', '-2.76773', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('161', '223.55', '9132.74', '-11.2427', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('162', '32.157', '9120.4', '-16.5454', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('163', '-160.425', '9053.54', '4.52803', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('164', '-1066.97', '8066.54', '-38.9822', '4.0817', '3518', '0', '530', '3', 'Northwind Cleft');
INSERT INTO `graveyards` VALUES ('165', '-1654.37', '7938.99', '-46.2106', '4.0817', '3518', '0', '530', '3', 'Halaa');
INSERT INTO `graveyards` VALUES ('166', '-1793.42', '4931.61', '-22.2098', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('167', '-2540.15', '3866.65', '10.0412', '4.0817', '3519', '0', '530', '3', 'Raastok Glade');
INSERT INTO `graveyards` VALUES ('168', '-699.699', '8883.16', '185.34', '4.0817', '3518', '0', '530', '3', 'Warmaul Hill');
INSERT INTO `graveyards` VALUES ('169', '-1000.13', '9045.47', '91.6882', '4.0817', '3518', '0', '530', '3', 'Warmaul Hill');
INSERT INTO `graveyards` VALUES ('170', '-1983.42', '9361.21', '72.7727', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('171', '-2153.3', '9323.71', '52.5836', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('172', '-2619.46', '8953.7', '-11.71', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('173', '-2799.85', '8785.75', '-42.808', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('174', '-2984.12', '8700.11', '-53.429', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('175', '-2989.35', '8445.13', '-36.1422', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('176', '-3122.56', '8079.49', '-49.1322', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('177', '-3155.75', '7316.31', '-25.8292', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('178', '-3244.7', '7079.02', '-49.7009', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('179', '-2987.35', '7045.47', '-53.9469', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('180', '-2962.33', '6796.88', '-51.1737', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('181', '-3040.6', '6534.85', '98.9149', '4.0817', '3518', '0', '530', '3', 'Kil sorrow Fortress');
INSERT INTO `graveyards` VALUES ('182', '-3379.58', '6206.48', '-3.6654', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('183', '-3621.98', '6225.18', '-19.6565', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('184', '-3898.57', '6147.65', '-36.9816', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('185', '-3844.34', '5931.41', '-25.1268', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('186', '-3801.34', '5618.75', '-27.0187', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('187', '-3910.99', '5404.07', '-35.8346', '4.0817', '3519', '0', '530', '3', 'The Bone Wastes');
INSERT INTO `graveyards` VALUES ('188', '-3886.29', '5149.57', '-59.4969', '4.0817', '3519', '0', '530', '3', 'The Bone Wastes');
INSERT INTO `graveyards` VALUES ('189', '-3990.14', '4869.48', '-107.895', '4.0817', '3519', '0', '530', '3', 'The Bone Wastes');
INSERT INTO `graveyards` VALUES ('190', '-3904.3', '4591.4', '-46.3185', '4.0817', '3519', '0', '530', '3', 'The Bone Wastes');
INSERT INTO `graveyards` VALUES ('191', '-4024.3', '4421.72', '-49.6202', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('192', '-3965.06', '4128.62', '0.234531', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('193', '-2415.76', '1811.62', '-1.03827', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('194', '-2319.13', '1749.94', '-13.3954', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('195', '-2447.42', '1612.81', '-27.3879', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('196', '-2650.24', '1666.66', '9.50848', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('197', '-4151.09', '3425.82', '292.965', '4.0817', '3519', '0', '530', '3', 'Blackwind Valley');
INSERT INTO `graveyards` VALUES ('198', '-2667.79', '3046.76', '-7.50784', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('199', '-2375.42', '2848.08', '-70.0744', '4.0817', '3540', '0', '530', '3', 'Twisting Nether');
INSERT INTO `graveyards` VALUES ('200', '-2205.61', '2968.3', '-69.6146', '4.0817', '3540', '0', '530', '3', 'Twisting Nether');
INSERT INTO `graveyards` VALUES ('201', '-2098.93', '3116.51', '-51.0518', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('202', '-2047.74', '3278.56', '-61.7716', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('203', '-2059', '3560.39', '-74.1911', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('204', '-1876.5', '3700.5', '-18.8745', '4.0817', '3519', '0', '530', '3', 'Terokkar Forest');
INSERT INTO `graveyards` VALUES ('205', '0', '0', '-1189.81', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('206', '-1289.79', '9166.72', '218.117', '4.0817', '3518', '0', '530', '3', 'The Twilight Ridge');
INSERT INTO `graveyards` VALUES ('207', '-856.214', '6600.06', '173.564', '4.0817', '3518', '0', '530', '3', 'Elemental Plateau');
INSERT INTO `graveyards` VALUES ('208', '-2033.53', '8479.53', '-0.444271', '4.0817', '3518', '0', '530', '3', 'Nagrand');
INSERT INTO `graveyards` VALUES ('209', '700.091', '2207.99', '288.51', '4.0817', '3483', '0', '530', '3', 'Throne of Kil jaeden');
INSERT INTO `graveyards` VALUES ('210', '-249.765', '1023.32', '41.6667', '4.0817', '3483', '0', '530', '3', 'The Stair of Destiny');
INSERT INTO `graveyards` VALUES ('211', '-3648.33', '5116.13', '-22.7089', '4.0817', '3519', '0', '530', '3', 'Auchindoun');
INSERT INTO `graveyards` VALUES ('212', '874.911', '7284.72', '23.0023', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('213', '337.125', '8616.87', '24.1361', '4.0817', '3521', '0', '530', '3', 'Zangarmarsh');
INSERT INTO `graveyards` VALUES ('214', '4363.88', '3093.74', '132.969', '4.0817', '3523', '0', '530', '3', 'The Stormspire');
INSERT INTO `graveyards` VALUES ('215', '3032.44', '3594.28', '145.806', '4.817', '3523', '0', '530', '3', 'Area 52');
INSERT INTO `graveyards` VALUES ('216', '-2999.23', '2439.06', '62.341', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Village');
INSERT INTO `graveyards` VALUES ('217', '-4022.99', '2048.58', '96.8575', '4.0817', '3520', '0', '530', '3', 'Wildhammer Stronghold');
INSERT INTO `graveyards` VALUES ('218', '1955.9', '6768.81', '164.023', '4.0817', '3522', '0', '530', '3', 'Sylvanaar');
INSERT INTO `graveyards` VALUES ('219', '2218.9', '6017.35', '135.921', '4.0817', '3522', '0', '530', '3', 'Thunderlord Stronghold');
INSERT INTO `graveyards` VALUES ('220', '-3962.35', '3667.08', '289.088', '4.0817', '3519', '0', '530', '3', 'Blackwind Valley');
INSERT INTO `graveyards` VALUES ('221', '-2652.66', '1484.21', '23.1527', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('222', '-2477.69', '1386.24', '47.421', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('223', '-2459.08', '1277.57', '33.6144', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('224', '-2464.28', '1074.65', '33.3692', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('225', '-2597.45', '1040.72', '40.4363', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('226', '-2753.67', '966.146', '-3.6132', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('227', '-2721.16', '711.034', '-21.3212', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('228', '-2752.54', '509.309', '-25.5289', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('229', '-3004.49', '482.051', '-15.285', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('230', '-2997.38', '207.579', '3.01474', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('231', '-4084.62', '120.513', '63.1184', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('232', '-4231.62', '58.6267', '6.84955', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('233', '-4445.81', '224.844', '94.9099', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('234', '-4507.6', '553.553', '123.951', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('235', '-4445.43', '863.558', '6.49986', '4.0817', '3520', '0', '530', '3', 'Netherwing Fields');
INSERT INTO `graveyards` VALUES ('236', '-4791.52', '1082.18', '-8.79358', '4.0817', '3520', '0', '530', '3', 'Netherwing Fields');
INSERT INTO `graveyards` VALUES ('237', '-4618.17', '1850.61', '153.303', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('238', '-4568.14', '2023.8', '89.6597', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('239', '-4541.32', '2281.76', '17.979', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('240', '-4408.89', '2328.78', '31.728', '4.0817', '3520', '0', '530', '3', 'Shadowmoon Valley');
INSERT INTO `graveyards` VALUES ('241', '1933', '7389.18', '364.941', '4.0817', '3522', '0', '530', '3', 'Vortex Pinnacle');
INSERT INTO `graveyards` VALUES ('242', '2356.31', '7345.09', '363.442', '4.0817', '3522', '0', '530', '3', 'Vortex Pinnacle');
INSERT INTO `graveyards` VALUES ('243', '2825.15', '7269.15', '365.266', '4.0817', '3522', '0', '530', '3', 'Forge Camp: Wrath');
INSERT INTO `graveyards` VALUES ('244', '3199.99', '7264.96', '146.993', '4.0817', '3522', '0', '530', '3', 'Blade s Edge Mountains');
INSERT INTO `graveyards` VALUES ('245', '3432.89', '7312.38', '138.71', '4.0817', '3522', '0', '530', '3', 'Raven s Wood');
INSERT INTO `graveyards` VALUES ('246', '3753.24', '7118.03', '141.365', '4.0817', '3522', '0', '530', '3', 'Raven s Wood');
INSERT INTO `graveyards` VALUES ('247', '3797.19', '6900.24', '141.658', '4.0817', '3522', '0', '530', '3', 'Raven s Wood');
INSERT INTO `graveyards` VALUES ('248', '3839.15', '6586.81', '134.665', '4.0817', '3522', '0', '530', '3', 'Grishnath');
INSERT INTO `graveyards` VALUES ('249', '3477.33', '6500.25', '133.395', '4.0817', '3522', '0', '530', '3', 'Raven s Wood');
INSERT INTO `graveyards` VALUES ('250', '3664.81', '6205.21', '262.368', '4.0817', '3522', '0', '530', '3', 'Bash ir Landing');
INSERT INTO `graveyards` VALUES ('251', '3989.04', '6089.92', '262.605', '4.0817', '3522', '0', '530', '3', 'Bash ir Landing');
INSERT INTO `graveyards` VALUES ('252', '4095.11', '5811.89', '259.778', '4.0817', '3522', '0', '530', '3', 'Felstorm Point');
INSERT INTO `graveyards` VALUES ('253', '4152.64', '5499.22', '274.249', '4.0817', '3522', '0', '530', '3', 'Felstorm Point');
INSERT INTO `graveyards` VALUES ('254', '4120.71', '5214.15', '264.997', '4.0817', '3522', '0', '530', '3', 'The Signing Ridge');
INSERT INTO `graveyards` VALUES ('255', '4086.35', '4849.9', '266.545', '4.0817', '3522', '0', '530', '3', 'The Signing Ridge');
INSERT INTO `graveyards` VALUES ('256', '3926.2', '4825.28', '264.974', '4.0817', '3522', '0', '530', '3', 'The Signing Ridge');
INSERT INTO `graveyards` VALUES ('257', '3733.34', '4735.75', '241.414', '4.0817', '3522', '0', '530', '3', 'Skald');
INSERT INTO `graveyards` VALUES ('258', '3455.31', '4468.35', '154.198', '4.0817', '3522', '0', '530', '3', 'Broken Wilds');
INSERT INTO `graveyards` VALUES ('259', '3323.6', '4503.88', '152.428', '4.0817', '3522', '0', '530', '3', 'Broken Wilds');
INSERT INTO `graveyards` VALUES ('260', '2877.52', '4738.91', '278.92', '4.0817', '3522', '0', '530', '3', 'Forge Camp: Anger');
INSERT INTO `graveyards` VALUES ('261', '2653', '5100.26', '275.421', '4.0817', '3522', '0', '530', '3', 'Ridge of Madness');
INSERT INTO `graveyards` VALUES ('262', '2344.62', '5072.5', '267.939', '4.0817', '3522', '0', '530', '3', 'Ridge of Madness');
INSERT INTO `graveyards` VALUES ('263', '2251.08', '4907.94', '140.469', '4.0817', '3522', '0', '530', '3', 'Vekhaar Stand');
INSERT INTO `graveyards` VALUES ('264', '2274.35', '4725.43', '160.179', '4.0817', '3522', '0', '530', '3', 'Blade s Edge Mountains');
INSERT INTO `graveyards` VALUES ('265', '2102.66', '4685.08', '140.251', '4.0817', '3522', '0', '530', '3', 'Mok Nathal Village');
INSERT INTO `graveyards` VALUES ('266', '1914.58', '4677.85', '133.398', '4.0817', '3522', '0', '530', '3', 'Vekhaar Stand');
INSERT INTO `graveyards` VALUES ('267', '1771.94', '4585.16', '144.841', '4.0817', '3522', '0', '530', '3', 'Veil Vekh');
INSERT INTO `graveyards` VALUES ('268', '1621.04', '4563.14', '137.216', '4.0817', '3522', '0', '530', '3', 'Veil Vekh');
INSERT INTO `graveyards` VALUES ('269', '1606.36', '4792.58', '138.904', '4.0817', '3522', '0', '530', '3', 'Vekhaar Stand');
INSERT INTO `graveyards` VALUES ('270', '1596.31', '4948.65', '169.925', '4.0817', '3522', '0', '530', '3', 'Vekhaar Stand');
INSERT INTO `graveyards` VALUES ('271', '1616.9', '5077.05', '174.748', '4.0817', '3522', '0', '530', '3', 'Trogma s Claim');
INSERT INTO `graveyards` VALUES ('272', '3491.41', '4127.39', '119.768', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('273', '3578.56', '3957.1', '117.991', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('274', '3586.96', '3717.31', '114.6', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('275', '3640.77', '352.84', '103.858', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('276', '3520.2', '3511.7', '125.479', '4.0817', '3523', '0', '530', '3', 'Ruins of Enkaat');
INSERT INTO `graveyards` VALUES ('277', '3399.31', '3400.41', '102.136', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('278', '3271.49', '3366.92', '105.545', '4.0817', '3523', '0', '530', '3', 'Netherstorm');
INSERT INTO `graveyards` VALUES ('279', '3188.37', '3257.08', '88.3148', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('280', '3022.79', '3163.7', '118.86', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('281', '2943.66', '3056.64', '113.385', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('282', '2846.52', '2955.54', '113.449', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('283', '2815.3', '2830.89', '75.4329', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('284', '2695.05', '2940.24', '94.6529', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('285', '2570.5', '3135.96', '108.157', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('286', '2511.98', '3275.15', '99.7674', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('287', '2449.93', '3377.49', '114.96', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('288', '2519.66', '3538.7', '120.709', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('289', '2479.84', '3695.68', '106.605', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('290', '2433.44', '3835.28', '95.6042', '4.0817', '3523', '0', '530', '3', 'The Heap');
INSERT INTO `graveyards` VALUES ('291', '2403.43', '3995.29', '99.0321', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('292', '2477.41', '4151.27', '114.135', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('293', '2535.26', '4396.42', '103.363', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('294', '2719.93', '4456.6', '101.212', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('295', '2916.15', '4444.49', '111.565', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('296', '3069.1', '4357.14', '118.812', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('297', '3091.8', '4146.84', '125.181', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('298', '3221.17', '4069.1', '102.671', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('299', '3355.79', '4149.28', '138.087', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('300', '3980.61', '4262.21', '129.993', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('301', '3799.93', '4217.95', '105.808', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('302', '3744.13', '4010.94', '101.939', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('303', '3796.27', '3772.19', '100.353', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('304', '4049.61', '3692.78', '101.661', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('305', '4152.53', '3886.21', '120.431', '4.0817', '3523', '0', '530', '3', 'Manaforge Ara');
INSERT INTO `graveyards` VALUES ('306', '4235.16', '4080.62', '95.3036', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('307', '4169.83', '4209.06', '117.895', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('308', '3836.08', '3477.26', '75.412', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('309', '3994.95', '3538.27', '121.792', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('310', '4211.4', '3632', '124.094', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('311', '4395.24', '3708.62', '95.6164', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('312', '4580.69', '3584', '94.033', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('313', '4793.19', '3527.37', '102.017', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('314', '4903.71', '3323.86', '101.859', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('315', '4945.87', '3110.83', '98.0965', '4.0817', '3523', '0', '530', '3', 'Eco-Dome Farfield');
INSERT INTO `graveyards` VALUES ('316', '5156.75', '2974.21', '75.4612', '4.0817', '3523', '0', '530', '3', 'Eco-Dome Farfield');
INSERT INTO `graveyards` VALUES ('317', '5204.7', '2868.11', '53.9315', '4.0817', '3523', '0', '530', '3', 'Eco-Dome Farfield');
INSERT INTO `graveyards` VALUES ('318', '5019.97', '2798.73', '51.2722', '4.0817', '3523', '0', '530', '3', 'Eco-Dome Farfield');
INSERT INTO `graveyards` VALUES ('319', '4885.18', '2663.13', '85.2444', '4.0817', '3523', '0', '530', '3', 'Netherstone');
INSERT INTO `graveyards` VALUES ('320', '4853.17', '2354.02', '101.436', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('321', '4680.81', '2287.48', '129.047', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('322', '4522.44', '2280.28', '136.765', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('323', '4436.57', '2485.48', '90.1471', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('324', '4448.3', '2658.15', '111.544', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('325', '4285.06', '2837.04', '100.961', '4.0817', '3523', '0', '530', '3', 'The Stormspire');
INSERT INTO `graveyards` VALUES ('326', '4136.62', '2699.33', '100.346', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('327', '3975.24', '2807.44', '115.994', '4.0817', '3523', '0', '530', '3', 'The Stormspire');
INSERT INTO `graveyards` VALUES ('328', '3931.79', '3020.67', '103.842', '4.0817', '3523', '0', '530', '3', 'The Stormspire');
INSERT INTO `graveyards` VALUES ('329', '3895.88', '3257.64', '120.084', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('330', '3629.32', '3097.21', '111.865', '4.0817', '3523', '0', '530', '3', 'Eco-Dome Midrealm');
INSERT INTO `graveyards` VALUES ('331', '3476.45', '3293.56', '95.2325', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('332', '3348.41', '3172.06', '90.9979', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('333', '3216.28', '2992.5', '124.193', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('334', '3008.05', '2902.59', '74.1978', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('335', '2860.47', '2735.28', '87.7933', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('336', '2863.8', '2537.41', '104.721', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('337', '2856.08', '2297.04', '98.8206', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('338', '2834.86', '2040.24', '92.1341', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('339', '2868.81', '1848.69', '96.9383', '4.0817', '3523', '0', '530', '3', 'The Tempest Rift');
INSERT INTO `graveyards` VALUES ('340', '2895.75', '1708.09', '105.052', '4.0817', '3523', '0', '530', '3', 'The Tempest Rift');
INSERT INTO `graveyards` VALUES ('341', '3110.67', '1624.43', '112.188', '4.0817', '3523', '0', '530', '3', 'The Tempest Rift');
INSERT INTO `graveyards` VALUES ('342', '3276.02', '1726.59', '101.664', '4.0817', '3523', '0', '530', '3', 'The Tempest Rift');
INSERT INTO `graveyards` VALUES ('343', '3332.26', '1986.97', '95.2601', '4.0817', '3523', '0', '530', '3', 'The Vortex Fields');
INSERT INTO `graveyards` VALUES ('344', '3315.85', '2185.52', '109.184', '4.0817', '3523', '0', '530', '3', 'The Vortex Fields');
INSERT INTO `graveyards` VALUES ('345', '3384.58', '2376.22', '73.8488', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('346', '3492.84', '2570.84', '139.119', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('347', '3590.41', '2677.08', '135.727', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('348', '3740.94', '2696.99', '113.251', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('349', '3737.85', '2894.69', '100.685', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('350', '3850.8', '2556.63', '75.1947', '4.0817', '3523', '0', '530', '3', 'Ethereum Staging Grounds');
INSERT INTO `graveyards` VALUES ('351', '3649.02', '2405.76', '74.7964', '4.0817', '3523', '0', '530', '3', 'Ethereum Staging Grounds');
INSERT INTO `graveyards` VALUES ('352', '3546.97', '2219.76', '92.3245', '4.0817', '3523', '0', '530', '3', 'Ethereum Staging Grounds');
INSERT INTO `graveyards` VALUES ('353', '3550.01', '2002.35', '92.6225', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('354', '3509.69', '1762.49', '75.1458', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('355', '3645.26', '1712.66', '106.572', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('356', '3681.18', '1558.56', '103.807', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('357', '3775.55', '1437.54', '-152.88', '4.0817', '3523', '0', '530', '3', 'Celestial Ridge');
INSERT INTO `graveyards` VALUES ('358', '3969.01', '1336.41', '-143.136', '4.0817', '3523', '0', '530', '3', 'Celestial Ridge');
INSERT INTO `graveyards` VALUES ('359', '4166.45', '1329.15', '-150.287', '4.0817', '3523', '0', '530', '3', 'Celestial Ridge');
INSERT INTO `graveyards` VALUES ('360', '4199.54', '1484.24', '-127.591', '4.0817', '3523', '0', '530', '3', 'Celestial Ridge');
INSERT INTO `graveyards` VALUES ('361', '4258.28', '1672.84', '113.242', '4.0817', '3523', '0', '530', '3', 'Celestial Ridge');
INSERT INTO `graveyards` VALUES ('362', '4362.23', '1927.16', '97.0053', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('363', '4347.15', '2143.36', '118.021', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('364', '4246.96', '2450.75', '90.9939', '4.0817', '3523', '0', '530', '3', 'Voidwind Plateau');
INSERT INTO `graveyards` VALUES ('365', '4116.44', '2331.31', '93.833', '4.0817', '3523', '0', '530', '3', 'Ethereum Staging Grounds');
INSERT INTO `graveyards` VALUES ('366', '3972.86', '2444.21', '102.406', '4.0817', '3523', '0', '530', '3', 'Ethereum Staging Grounds');
INSERT INTO `graveyards` VALUES ('367', '2486.85', '1981.84', '88.0831', '4.0817', '3523', '0', '530', '3', 'Chapel Yard');
INSERT INTO `graveyards` VALUES ('368', '2568.91', '2143.99', '99.0477', '4.0817', '3523', '0', '530', '3', 'Kirin Var Village');
INSERT INTO `graveyards` VALUES ('369', '2648.16', '2353.63', '92.5609', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('370', '2659.25', '2547.14', '110.432', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('371', '2599.03', '2713', '104.399', '4.0817', '3523', '0', '530', '3', 'Manaforge Coruu');
INSERT INTO `graveyards` VALUES ('372', '2473.63', '2964.98', '106.197', '4.0817', '3523', '0', '530', '3', 'Manaforge Coruu');
INSERT INTO `graveyards` VALUES ('373', '2209.18', '2901.68', '93.8214', '4.0817', '3523', '0', '530', '3', 'Manaforge Coruu');
INSERT INTO `graveyards` VALUES ('374', '2164.32', '2667.39', '78.0574', '4.0817', '3523', '0', '530', '3', 'Manaforge Coruu');
INSERT INTO `graveyards` VALUES ('375', '2087', '2442.42', '72.1118', '4.0817', '3523', '0', '530', '3', 'The Crumbling Waste');
INSERT INTO `graveyards` VALUES ('376', '2079.82', '2227.04', '68.5153', '4.0817', '3523', '0', '530', '3', 'Kirin Var Village');
INSERT INTO `graveyards` VALUES ('377', '2240.18', '2067.8', '61.9474', '4.0817', '3523', '0', '530', '3', 'Kirin Var Village');
INSERT INTO `graveyards` VALUES ('378', '552.188', '1995.15', '103.703', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');
INSERT INTO `graveyards` VALUES ('379', '3065', '5426.42', '148.487', '4.0817', '3522', '0', '530', '3', 'Ruuan Weald');
INSERT INTO `graveyards` VALUES ('380', '3872.66', '5514.41', '271.81', '4.0817', '3522', '0', '530', '3', 'Felstorm Point');
INSERT INTO `graveyards` VALUES ('381', '2296.35', '7023.23', '364.134', '4.0817', '3522', '0', '530', '3', 'Vortex Pinnacle');
INSERT INTO `graveyards` VALUES ('382', '2312.27', '5083.93', '272.498', '4.0817', '3522', '0', '530', '3', 'Ridge of Madness');
INSERT INTO `graveyards` VALUES ('383', '101.144', '-184.934', '192.697', '4.0817', '36', '0', '0', '3', 'Growless Cave');
INSERT INTO `graveyards` VALUES ('384', '2980.19', '1869.82', '143.607', '4.0817', '3523', '0', '530', '3', 'Cosmowrench');
INSERT INTO `graveyards` VALUES ('385', '-1272.42', '2436.85', '64.0262', '4.0817', '3483', '0', '530', '3', 'Hellfire Peninsula');

-- ----------------------------
-- Table structure for `guilds`
-- ----------------------------
DROP TABLE IF EXISTS `guilds`;
CREATE TABLE `guilds` (
  `guildId` bigint(20) NOT NULL AUTO_INCREMENT,
  `guildName` varchar(32) NOT NULL DEFAULT '',
  `leaderGuid` bigint(20) NOT NULL DEFAULT '0',
  `emblemStyle` int(10) NOT NULL DEFAULT '0',
  `emblemColor` int(10) NOT NULL DEFAULT '0',
  `borderStyle` int(10) NOT NULL DEFAULT '0',
  `borderColor` int(10) NOT NULL DEFAULT '0',
  `backgroundColor` int(10) NOT NULL DEFAULT '0',
  `guildInfo` varchar(100) NOT NULL DEFAULT '',
  `motd` varchar(100) NOT NULL DEFAULT '',
  `createdate` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`guildId`),
  UNIQUE KEY `guildId` (`guildId`)
) ENGINE=MyISAM AUTO_INCREMENT=539 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of guilds
-- ----------------------------

-- ----------------------------
-- Table structure for `guild_ranks`
-- ----------------------------
DROP TABLE IF EXISTS `guild_ranks`;
CREATE TABLE `guild_ranks` (
  `guildId` int(6) unsigned NOT NULL DEFAULT '0',
  `rankId` int(1) NOT NULL DEFAULT '0',
  `rankName` varchar(255) NOT NULL DEFAULT '',
  `rankRights` int(3) unsigned NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of guild_ranks
-- ----------------------------

-- ----------------------------
-- Table structure for `instances`
-- ----------------------------
DROP TABLE IF EXISTS `instances`;
CREATE TABLE `instances` (
  `instanceid` int(11) NOT NULL DEFAULT '0',
  `mapid` int(11) NOT NULL DEFAULT '0',
  `npc_data` longtext NOT NULL,
  `player_data` longtext NOT NULL,
  `creation` int(15) NOT NULL DEFAULT '0',
  `expire` int(15) NOT NULL DEFAULT '0',
  `difficulty` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`instanceid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of instances
-- ----------------------------

-- ----------------------------
-- Table structure for `ipbans`
-- ----------------------------
DROP TABLE IF EXISTS `ipbans`;
CREATE TABLE `ipbans` (
  `ip` varchar(50) NOT NULL,
  `time` int(30) NOT NULL,
  PRIMARY KEY (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ipbans
-- ----------------------------

-- ----------------------------
-- Table structure for `itemloot`
-- ----------------------------
DROP TABLE IF EXISTS `itemloot`;
CREATE TABLE `itemloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) unsigned NOT NULL DEFAULT '0',
  `itemid` int(11) unsigned NOT NULL DEFAULT '25',
  `percentchance` float NOT NULL DEFAULT '1',
  PRIMARY KEY (`index`),
  KEY `i_gameobj_loot_entry` (`entryid`)
) ENGINE=MyISAM AUTO_INCREMENT=2460 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of itemloot
-- ----------------------------

-- ----------------------------
-- Table structure for `itempages`
-- ----------------------------
DROP TABLE IF EXISTS `itempages`;
CREATE TABLE `itempages` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `text` longtext NOT NULL,
  `next_page` int(20) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of itempages
-- ----------------------------
INSERT INTO `itempages` VALUES ('1', 'awd', '0');

-- ----------------------------
-- Table structure for `items`
-- ----------------------------
DROP TABLE IF EXISTS `items`;
CREATE TABLE `items` (
  `entry` int(255) unsigned NOT NULL DEFAULT '0',
  `class` int(30) NOT NULL DEFAULT '0',
  `subclass` int(30) NOT NULL DEFAULT '0',
  `field4` int(10) NOT NULL DEFAULT '-1',
  `name` varchar(255) NOT NULL DEFAULT '',
  `name2` varchar(255) NOT NULL DEFAULT '',
  `name3` varchar(255) NOT NULL DEFAULT '',
  `name4` varchar(255) NOT NULL DEFAULT '',
  `displayid` int(70) unsigned NOT NULL DEFAULT '0',
  `quality` int(30) NOT NULL DEFAULT '0',
  `flags` int(30) NOT NULL DEFAULT '0',
  `buyprice` int(30) NOT NULL DEFAULT '0',
  `sellprice` int(30) NOT NULL DEFAULT '0',
  `inventorytype` int(30) NOT NULL DEFAULT '0',
  `allowableclass` int(30) NOT NULL DEFAULT '0',
  `allowablerace` int(30) NOT NULL DEFAULT '0',
  `itemlevel` int(30) NOT NULL DEFAULT '0',
  `requiredlevel` int(30) NOT NULL DEFAULT '0',
  `RequiredSkill` int(30) NOT NULL DEFAULT '0',
  `RequiredSkillRank` int(30) NOT NULL DEFAULT '0',
  `RequiredSkillSubRank` int(30) NOT NULL DEFAULT '0',
  `RequiredPlayerRank1` int(30) NOT NULL DEFAULT '0',
  `RequiredPlayerRank2` int(30) NOT NULL DEFAULT '0',
  `RequiredFaction` int(30) NOT NULL DEFAULT '0',
  `RequiredFactionStanding` int(30) NOT NULL DEFAULT '0',
  `Unique` int(30) NOT NULL DEFAULT '0',
  `maxcount` int(30) NOT NULL DEFAULT '0',
  `ContainerSlots` int(30) NOT NULL DEFAULT '0',
  `stat_type1` int(30) NOT NULL DEFAULT '0',
  `stat_value1` int(30) NOT NULL DEFAULT '0',
  `stat_type2` int(30) NOT NULL DEFAULT '0',
  `stat_value2` int(30) NOT NULL DEFAULT '0',
  `stat_type3` int(30) NOT NULL DEFAULT '0',
  `stat_value3` int(30) NOT NULL DEFAULT '0',
  `stat_type4` int(30) NOT NULL DEFAULT '0',
  `stat_value4` int(30) NOT NULL DEFAULT '0',
  `stat_type5` int(30) NOT NULL DEFAULT '0',
  `stat_value5` int(30) NOT NULL DEFAULT '0',
  `stat_type6` int(30) NOT NULL DEFAULT '0',
  `stat_value6` int(30) NOT NULL DEFAULT '0',
  `stat_type7` int(30) NOT NULL DEFAULT '0',
  `stat_value7` int(30) NOT NULL DEFAULT '0',
  `stat_type8` int(30) NOT NULL DEFAULT '0',
  `stat_value8` int(30) NOT NULL DEFAULT '0',
  `stat_type9` int(30) NOT NULL DEFAULT '0',
  `stat_value9` int(30) NOT NULL DEFAULT '0',
  `stat_type10` int(30) NOT NULL DEFAULT '0',
  `stat_value10` int(30) NOT NULL DEFAULT '0',
  `dmg_min1` float NOT NULL DEFAULT '0',
  `dmg_max1` float NOT NULL DEFAULT '0',
  `dmg_type1` int(30) NOT NULL DEFAULT '0',
  `dmg_min2` float NOT NULL DEFAULT '0',
  `dmg_max2` float NOT NULL DEFAULT '0',
  `dmg_type2` int(30) NOT NULL DEFAULT '0',
  `dmg_min3` float NOT NULL DEFAULT '0',
  `dmg_max3` float NOT NULL DEFAULT '0',
  `dmg_type3` int(30) NOT NULL DEFAULT '0',
  `dmg_min4` float NOT NULL DEFAULT '0',
  `dmg_max4` float NOT NULL DEFAULT '0',
  `dmg_type4` int(30) NOT NULL DEFAULT '0',
  `dmg_min5` float NOT NULL DEFAULT '0',
  `dmg_max5` float NOT NULL DEFAULT '0',
  `dmg_type5` int(30) NOT NULL DEFAULT '0',
  `armor` int(30) NOT NULL DEFAULT '0',
  `holy_res` int(30) NOT NULL DEFAULT '0',
  `fire_res` int(30) NOT NULL DEFAULT '0',
  `nature_res` int(30) NOT NULL DEFAULT '0',
  `frost_res` int(30) NOT NULL DEFAULT '0',
  `shadow_res` int(30) NOT NULL DEFAULT '0',
  `arcane_res` int(30) NOT NULL DEFAULT '0',
  `delay` int(30) NOT NULL DEFAULT '0',
  `ammo_type` int(30) NOT NULL DEFAULT '0',
  `range` float NOT NULL DEFAULT '0',
  `spellid_1` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_1` int(30) NOT NULL DEFAULT '0',
  `spellcharges_1` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_1` int(30) NOT NULL DEFAULT '0',
  `spellcategory_1` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_1` int(30) NOT NULL DEFAULT '0',
  `spellid_2` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_2` int(30) NOT NULL DEFAULT '0',
  `spellcharges_2` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_2` int(30) NOT NULL DEFAULT '0',
  `spellcategory_2` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_2` int(30) NOT NULL DEFAULT '0',
  `spellid_3` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_3` int(30) NOT NULL DEFAULT '0',
  `spellcharges_3` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_3` int(30) NOT NULL DEFAULT '0',
  `spellcategory_3` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_3` int(30) NOT NULL DEFAULT '0',
  `spellid_4` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_4` int(30) NOT NULL DEFAULT '0',
  `spellcharges_4` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_4` int(30) NOT NULL DEFAULT '0',
  `spellcategory_4` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_4` int(30) NOT NULL DEFAULT '0',
  `spellid_5` int(30) NOT NULL DEFAULT '0',
  `spelltrigger_5` int(30) NOT NULL DEFAULT '0',
  `spellcharges_5` int(30) NOT NULL DEFAULT '0',
  `spellcooldown_5` int(30) NOT NULL DEFAULT '0',
  `spellcategory_5` int(30) NOT NULL DEFAULT '0',
  `spellcategorycooldown_5` int(30) NOT NULL DEFAULT '0',
  `bonding` int(30) NOT NULL DEFAULT '0',
  `description` varchar(255) NOT NULL DEFAULT '',
  `page_id` int(30) NOT NULL DEFAULT '0',
  `page_language` int(30) NOT NULL DEFAULT '0',
  `page_material` int(30) NOT NULL DEFAULT '0',
  `quest_id` int(30) NOT NULL DEFAULT '0',
  `lock_id` int(30) NOT NULL DEFAULT '0',
  `lock_material` int(30) NOT NULL DEFAULT '0',
  `sheathID` int(30) NOT NULL DEFAULT '0',
  `randomprop` int(30) NOT NULL DEFAULT '0',
  `unk203_1` int(11) NOT NULL DEFAULT '0',
  `block` int(30) NOT NULL DEFAULT '0',
  `itemset` int(30) NOT NULL DEFAULT '0',
  `MaxDurability` int(30) NOT NULL DEFAULT '0',
  `ZoneNameID` int(30) NOT NULL DEFAULT '0',
  `mapid` int(30) DEFAULT NULL,
  `bagfamily` int(30) NOT NULL DEFAULT '0',
  `TotemCategory` int(30) DEFAULT NULL,
  `socket_color_1` int(30) DEFAULT NULL,
  `unk201_3` int(30) NOT NULL DEFAULT '0',
  `socket_color_2` int(30) DEFAULT NULL,
  `unk201_5` int(30) NOT NULL DEFAULT '0',
  `socket_color_3` int(30) DEFAULT NULL,
  `unk201_7` int(30) NOT NULL DEFAULT '0',
  `socket_bonus` int(30) DEFAULT NULL,
  `GemProperties` int(30) DEFAULT NULL,
  `ItemExtendedCost` int(30) DEFAULT NULL,
  `ReqDisenchantSkill` int(30) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of items
-- ----------------------------
INSERT INTO `items` VALUES ('1', '0', '0', '-1', 'test', '', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, '0', null, null, '0', null, '0', null, '0', null, null, null, '-1');

-- ----------------------------
-- Table structure for `lootrandomprop`
-- ----------------------------
DROP TABLE IF EXISTS `lootrandomprop`;
CREATE TABLE `lootrandomprop` (
  `entryid` int(11) NOT NULL DEFAULT '0',
  `propid` int(11) NOT NULL DEFAULT '0',
  `percentchance` float DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of lootrandomprop
-- ----------------------------

-- ----------------------------
-- Table structure for `mailbox`
-- ----------------------------
DROP TABLE IF EXISTS `mailbox`;
CREATE TABLE `mailbox` (
  `message_id` int(30) NOT NULL DEFAULT '0',
  `message_type` int(30) NOT NULL DEFAULT '0',
  `player_guid` int(30) NOT NULL DEFAULT '0',
  `sender_guid` int(30) NOT NULL DEFAULT '0',
  `subject` varchar(255) NOT NULL DEFAULT '',
  `body` longtext NOT NULL,
  `money` int(30) NOT NULL DEFAULT '0',
  `attached_item_guid` bigint(30) NOT NULL DEFAULT '0',
  `cod` int(30) NOT NULL DEFAULT '0',
  `stationary` int(30) NOT NULL DEFAULT '0',
  `expiry_time` int(30) NOT NULL DEFAULT '0',
  `delivery_time` int(30) NOT NULL DEFAULT '0',
  `copy_made` int(30) NOT NULL DEFAULT '0',
  `read_flag` int(30) NOT NULL DEFAULT '0',
  `deleted_flag` int(30) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of mailbox
-- ----------------------------

-- ----------------------------
-- Table structure for `npc_gossip_textid`
-- ----------------------------
DROP TABLE IF EXISTS `npc_gossip_textid`;
CREATE TABLE `npc_gossip_textid` (
  `entryid` int(30) NOT NULL DEFAULT '0',
  `textid` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`entryid`),
  UNIQUE KEY `index` (`entryid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of npc_gossip_textid
-- ----------------------------

-- ----------------------------
-- Table structure for `npc_monstersay`
-- ----------------------------
DROP TABLE IF EXISTS `npc_monstersay`;
CREATE TABLE `npc_monstersay` (
  `entry` int(11) NOT NULL,
  `event` int(11) NOT NULL,
  `chance` float NOT NULL,
  `language` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `monstername` longtext,
  `text0` longtext,
  `text1` longtext,
  `text2` longtext,
  `text3` longtext,
  `text4` longtext
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of npc_monstersay
-- ----------------------------

-- ----------------------------
-- Table structure for `npc_text`
-- ----------------------------
DROP TABLE IF EXISTS `npc_text`;
CREATE TABLE `npc_text` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `prob0` float NOT NULL DEFAULT '0',
  `text0_0` longtext NOT NULL,
  `text0_1` longtext NOT NULL,
  `lang0` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em0_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob1` float NOT NULL DEFAULT '0',
  `text1_0` longtext NOT NULL,
  `text1_1` longtext NOT NULL,
  `lang1` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em1_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob2` float NOT NULL DEFAULT '0',
  `text2_0` longtext NOT NULL,
  `text2_1` longtext NOT NULL,
  `lang2` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em2_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob3` float NOT NULL DEFAULT '0',
  `text3_0` longtext NOT NULL,
  `text3_1` longtext NOT NULL,
  `lang3` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em3_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob4` float NOT NULL DEFAULT '0',
  `text4_0` longtext NOT NULL,
  `text4_1` longtext NOT NULL,
  `lang4` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em4_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob5` float NOT NULL DEFAULT '0',
  `text5_0` longtext NOT NULL,
  `text5_1` longtext NOT NULL,
  `lang5` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em5_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob6` float NOT NULL DEFAULT '0',
  `text6_0` longtext NOT NULL,
  `text6_1` longtext NOT NULL,
  `lang6` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em6_5` int(20) unsigned NOT NULL DEFAULT '0',
  `prob7` float NOT NULL DEFAULT '0',
  `text7_0` longtext NOT NULL,
  `text7_1` longtext NOT NULL,
  `lang7` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_0` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_1` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_2` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_3` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_4` int(20) unsigned NOT NULL DEFAULT '0',
  `em7_5` int(20) unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of npc_text
-- ----------------------------
INSERT INTO `npc_text` VALUES ('1', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', '0', '0', '0', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `objectloot`
-- ----------------------------
DROP TABLE IF EXISTS `objectloot`;
CREATE TABLE `objectloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(11) NOT NULL DEFAULT '0',
  `itemid` int(11) NOT NULL DEFAULT '0',
  `percentchance` float DEFAULT NULL,
  PRIMARY KEY (`index`),
  KEY `entryid` (`entryid`)
) ENGINE=MyISAM AUTO_INCREMENT=53071 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of objectloot
-- ----------------------------

-- ----------------------------
-- Table structure for `petdefaultspells`
-- ----------------------------
DROP TABLE IF EXISTS `petdefaultspells`;
CREATE TABLE `petdefaultspells` (
  `entry` int(11) NOT NULL DEFAULT '0',
  `spell` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of petdefaultspells
-- ----------------------------

-- ----------------------------
-- Table structure for `playercooldownitems`
-- ----------------------------
DROP TABLE IF EXISTS `playercooldownitems`;
CREATE TABLE `playercooldownitems` (
  `OwnerGuid` bigint(10) NOT NULL DEFAULT '0',
  `ItemEntry` int(10) NOT NULL DEFAULT '0',
  `SpellID` int(10) NOT NULL DEFAULT '0',
  `SpellCategory` int(10) NOT NULL DEFAULT '0',
  `CooldownTimeStamp` int(11) NOT NULL DEFAULT '0',
  `Cooldown` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playercooldownitems
-- ----------------------------

-- ----------------------------
-- Table structure for `playercooldownsecurity`
-- ----------------------------
DROP TABLE IF EXISTS `playercooldownsecurity`;
CREATE TABLE `playercooldownsecurity` (
  `OwnerGuid` bigint(10) NOT NULL DEFAULT '0',
  `SpellID` int(10) NOT NULL DEFAULT '0',
  `TimeStamp` int(10) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='InnoDB free: 123904 kB; InnoDB free: 123904 kB';

-- ----------------------------
-- Records of playercooldownsecurity
-- ----------------------------

-- ----------------------------
-- Table structure for `playercreateinfo`
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo`;
CREATE TABLE `playercreateinfo` (
  `Index` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `race` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `factiontemplate` int(5) NOT NULL DEFAULT '0',
  `class` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `mapID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `zoneID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  `displayID` smallint(5) unsigned NOT NULL DEFAULT '0',
  `BaseStrength` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseAgility` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseStamina` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseIntellect` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseSpirit` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BaseHealth` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseMana` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseRage` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseFocus` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `BaseEnergy` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `attackpower` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `mindmg` float NOT NULL DEFAULT '0',
  `maxdmg` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`Index`)
) ENGINE=MyISAM AUTO_INCREMENT=57 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playercreateinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `playercreateinfo_bars`
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo_bars`;
CREATE TABLE `playercreateinfo_bars` (
  `race` int(2) DEFAULT NULL,
  `class` int(2) DEFAULT NULL,
  `button` int(4) DEFAULT NULL,
  `action` int(4) DEFAULT NULL,
  `type` int(4) DEFAULT NULL,
  `misc` int(4) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playercreateinfo_bars
-- ----------------------------
INSERT INTO `playercreateinfo_bars` VALUES ('0', '1', '72', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '1', '73', '78', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '1', '83', '117', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '2', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '2', '2', '635', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '2', '1', '20154', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '2', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '2', '10', '2070', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '3', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '3', '2', '75', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '3', '1', '2973', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '3', '10', '4604', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '3', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '4', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '4', '1', '1752', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '4', '2', '2098', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '4', '11', '2070', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '5', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '5', '1', '585', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '5', '2', '2050', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '5', '10', '4540', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '5', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '7', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '7', '1', '403', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '7', '2', '331', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '7', '10', '4604', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '7', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '8', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '8', '1', '133', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '8', '2', '168', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '8', '10', '2070', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '8', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '11', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '11', '1', '5176', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '11', '2', '5185', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '11', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '11', '10', '4536', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '9', '1', '686', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '9', '2', '687', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '9', '10', '4604', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '9', '11', '159', '128', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '9', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('0', '4', '3', '2764', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '72', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '73', '78', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '74', '28880', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '83', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '84', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '96', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '1', '108', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '1', '20154', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '2', '635', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '3', '28880', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '11', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '2', '83', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '1', '2973', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '2', '75', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '3', '28880', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '11', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '72', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '73', '2973', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '74', '75', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '82', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '3', '83', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '1', '585', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '2', '2050', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '3', '28880', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '11', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '5', '83', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '7', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '7', '1', '403', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '7', '2', '331', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '7', '3', '28880', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '7', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '7', '11', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '1', '133', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '2', '168', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '3', '28880', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '11', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('11', '8', '83', '4540', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '1', '20154', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '2', '635', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '3', '28734', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '4', '28730', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '2', '11', '20857', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '1', '2973', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '2', '75', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '3', '28734', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '4', '28730', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '3', '11', '20857', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '1', '1752', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '2', '2098', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '3', '2764', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '4', '28734', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '5', '25046', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '4', '11', '20857', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '1', '585', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '2', '2050', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '3', '28734', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '4', '28730', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '5', '11', '20857', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '1', '133', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '2', '168', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '3', '28734', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '4', '28730', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '8', '11', '20857', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '0', '6603', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '1', '686', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '2', '687', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '3', '28734', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '4', '28730', '0', '0');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '10', '159', '0', '128');
INSERT INTO `playercreateinfo_bars` VALUES ('10', '9', '11', '20857', '0', '128');

-- ----------------------------
-- Table structure for `playercreateinfo_items`
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo_items`;
CREATE TABLE `playercreateinfo_items` (
  `indexid` int(4) NOT NULL DEFAULT '0',
  `protoid` int(4) NOT NULL DEFAULT '0',
  `slotid` int(10) NOT NULL DEFAULT '0',
  `amount` int(3) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playercreateinfo_items
-- ----------------------------
INSERT INTO `playercreateinfo_items` VALUES ('1', '38', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('1', '39', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('1', '40', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('1', '2362', '16', '1');
INSERT INTO `playercreateinfo_items` VALUES ('1', '25', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('1', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('1', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('2', '6125', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('2', '139', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('2', '140', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('2', '12282', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('2', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('2', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('3', '38', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('3', '39', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('3', '40', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('3', '12282', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('3', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('3', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('4', '6120', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('4', '6121', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('4', '6122', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('4', '2362', '16', '1');
INSERT INTO `playercreateinfo_items` VALUES ('4', '25', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('4', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('4', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('5', '6125', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('5', '139', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('5', '140', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('5', '2362', '16', '1');
INSERT INTO `playercreateinfo_items` VALUES ('5', '25', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('5', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('5', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('6', '6125', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('6', '139', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('6', '2361', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('6', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('6', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('7', '38', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('7', '39', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('7', '40', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('7', '2362', '16', '1');
INSERT INTO `playercreateinfo_items` VALUES ('7', '25', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('7', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('7', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('8', '6125', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('8', '139', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('8', '2362', '16', '1');
INSERT INTO `playercreateinfo_items` VALUES ('8', '25', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('8', '117', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('8', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('9', '45', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('9', '44', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('9', '43', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('9', '2361', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('9', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('9', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('9', '2070', '25', '4');
INSERT INTO `playercreateinfo_items` VALUES ('10', '45', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('10', '44', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('10', '43', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('10', '2361', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('10', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('10', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('10', '2070', '25', '4');
INSERT INTO `playercreateinfo_items` VALUES ('15', '148', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '147', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '129', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '2504', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '4604', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('15', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('15', '2101', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '2512', '19', '200');
INSERT INTO `playercreateinfo_items` VALUES ('11', '127', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '6126', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '6127', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '37', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '2504', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '4604', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('11', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('11', '2101', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '2512', '19', '200');
INSERT INTO `playercreateinfo_items` VALUES ('12', '148', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '147', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '129', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '37', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '2508', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '4604', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('12', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('12', '2102', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '2516', '19', '200');
INSERT INTO `playercreateinfo_items` VALUES ('16', '127', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('16', '6126', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('16', '37', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('16', '2508', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('16', '4604', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('16', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('16', '2102', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('16', '2516', '19', '200');
INSERT INTO `playercreateinfo_items` VALUES ('17', '127', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('17', '6126', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('17', '37', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('17', '2504', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('17', '4604', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('17', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('17', '2101', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('17', '2512', '19', '200');
INSERT INTO `playercreateinfo_items` VALUES ('18', '49', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('18', '48', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('18', '47', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('18', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('18', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('18', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('18', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('19', '2105', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('19', '120', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('19', '121', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('19', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('19', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('19', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('19', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('20', '49', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('20', '48', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('20', '47', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('20', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('20', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('20', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('20', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('21', '49', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('21', '48', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('21', '47', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('21', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('21', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('21', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('21', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('22', '2105', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('22', '120', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('22', '121', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('22', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('22', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('22', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('22', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('23', '49', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('23', '48', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('23', '47', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('23', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('23', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('23', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('23', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('24', '2105', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('24', '120', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('24', '121', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('24', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('24', '2947', '17', '200');
INSERT INTO `playercreateinfo_items` VALUES ('24', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('24', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '53', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '6098', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '52', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '51', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('25', '4540', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('25', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '53', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '6098', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '52', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '51', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('26', '4540', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('26', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '53', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '6119', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '52', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '51', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('27', '4540', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('27', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '53', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '6144', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '52', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '51', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('28', '4540', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('28', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('29', '53', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('29', '6144', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('29', '52', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('29', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('29', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('29', '4540', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('29', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('30', '154', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('30', '153', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('30', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('30', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('30', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('30', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('31', '154', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('31', '153', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('31', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('31', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('31', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('31', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('32', '6134', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('32', '153', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('32', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('32', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('32', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('32', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('34', '6096', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('34', '56', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('34', '1395', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('34', '55', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('34', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('34', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('34', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('34', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('35', '6096', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('35', '6140', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('35', '1395', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('35', '55', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('35', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('35', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('35', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('35', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('36', '6096', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('36', '56', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('36', '1395', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('36', '55', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('36', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('36', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('36', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('36', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('37', '6096', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('37', '6140', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('37', '1395', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('37', '55', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('37', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('37', '2070', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('37', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('37', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('38', '6097', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('38', '57', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('38', '1396', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('38', '59', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('38', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('38', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('38', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('38', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('39', '6129', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('39', '1396', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('39', '59', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('39', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('39', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('39', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('39', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('40', '6129', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('40', '1396', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('40', '59', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('40', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('40', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('40', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('40', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '6097', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '57', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '1396', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '59', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '2092', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '149', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('41', '4604', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('41', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('42', '6123', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('42', '6124', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('42', '3661', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('42', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('42', '4536', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('42', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('43', '6139', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('43', '6124', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('43', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('43', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('43', '4536', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('43', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('11', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('12', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('13', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('14', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('15', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('16', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('17', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('44', '23473', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('44', '23474', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('44', '23475', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('44', '23346', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('44', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('44', '4542', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('45', '23476', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('45', '23477', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('45', '2361', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('45', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('45', '4540', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('45', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('46', '23345', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '23344', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '23348', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '25', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '23347', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '2101', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('46', '4540', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('46', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('47', '6097', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('47', '23322', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('47', '1396', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('47', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('47', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('47', '4540', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('47', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('48', '23345', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('48', '23344', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('48', '23348', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('48', '36', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('48', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('48', '4540', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('48', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('49', '23473', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('49', '23479', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('49', '23478', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('49', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('49', '6948', '23', '1');
INSERT INTO `playercreateinfo_items` VALUES ('49', '4540', '24', '4');
INSERT INTO `playercreateinfo_items` VALUES ('49', '159', '25', '2');
INSERT INTO `playercreateinfo_items` VALUES ('50', '24143', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('50', '24145', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('50', '24146', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('50', '23346', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('50', '20857', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('50', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('50', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '20901', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '20899', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '20900', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '20982', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '20980', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '2101', '19', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '159', '23', '2');
INSERT INTO `playercreateinfo_items` VALUES ('51', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('51', '20857', '25', '4');
INSERT INTO `playercreateinfo_items` VALUES ('52', '20897', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('52', '20896', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('52', '20898', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('52', '20982', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('52', '25861', '17', '1');
INSERT INTO `playercreateinfo_items` VALUES ('52', '20857', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('52', '6948', '24', '1');
INSERT INTO `playercreateinfo_items` VALUES ('53', '53', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('53', '20891', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('53', '52', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('53', '51', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('53', '20981', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('53', '20857', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('53', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('53', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('54', '6096', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('54', '20893', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('54', '20894', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('54', '20895', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('54', '35', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('54', '20857', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('54', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('54', '6948', '25', '1');
INSERT INTO `playercreateinfo_items` VALUES ('55', '6097', '3', '1');
INSERT INTO `playercreateinfo_items` VALUES ('55', '20892', '4', '1');
INSERT INTO `playercreateinfo_items` VALUES ('55', '1396', '6', '1');
INSERT INTO `playercreateinfo_items` VALUES ('55', '59', '7', '1');
INSERT INTO `playercreateinfo_items` VALUES ('55', '20983', '15', '1');
INSERT INTO `playercreateinfo_items` VALUES ('55', '20857', '23', '4');
INSERT INTO `playercreateinfo_items` VALUES ('55', '159', '24', '2');
INSERT INTO `playercreateinfo_items` VALUES ('55', '6948', '25', '1');

-- ----------------------------
-- Table structure for `playercreateinfo_skills`
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo_skills`;
CREATE TABLE `playercreateinfo_skills` (
  `indexid` int(4) NOT NULL DEFAULT '0',
  `skillid` int(5) NOT NULL DEFAULT '0',
  `level` int(4) NOT NULL DEFAULT '0',
  `maxlevel` int(4) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playercreateinfo_skills
-- ----------------------------
INSERT INTO `playercreateinfo_skills` VALUES ('1', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '754', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('1', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '754', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '594', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '160', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('9', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '754', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('18', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '754', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('25', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '754', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '8', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '6', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('34', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '754', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '593', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '354', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('38', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '172', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '125', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('2', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '125', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '45', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('11', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '125', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('19', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '125', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '374', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '375', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('30', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '593', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '125', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '354', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('39', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '172', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '101', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '111', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('3', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '594', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '101', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '111', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '160', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('10', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '101', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '111', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '46', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('12', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '101', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '111', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('20', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '101', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '111', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('26', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '113', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '126', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('4', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '113', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '45', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '126', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('15', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '113', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '126', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('21', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '113', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '126', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('27', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '574', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '573', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '113', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '126', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('42', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '220', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '673', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '55', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('5', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '220', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '673', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('22', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '220', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '673', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('28', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '220', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '8', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '673', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '6', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('35', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '220', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '593', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '354', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '673', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('40', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '124', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '115', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '160', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('6', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '124', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '115', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '46', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('16', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '124', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '374', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '375', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '115', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('31', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '574', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '124', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '573', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '115', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('43', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '753', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '313', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('7', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '753', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '313', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('23', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '8', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '753', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '6', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '313', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('36', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '593', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '354', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '753', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '313', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('41', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '315', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '733', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('8', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '315', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '733', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '44', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '45', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('17', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '315', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '733', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('24', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '315', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '733', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('29', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '315', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '374', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '375', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '733', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('32', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '8', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '315', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '733', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '6', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('37', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '759', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '26', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '45', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '473', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '137', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '2026', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '46', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '293', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '257', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '229', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '136', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '760', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '160', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '109', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '226', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '118', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '176', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '55', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('44', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '759', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '137', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '594', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '293', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '229', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '760', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '43', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '160', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '109', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '184', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '55', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '267', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('45', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '759', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '45', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '413', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '473', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '137', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '46', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '229', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '136', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '760', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '109', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '226', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '118', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '176', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '55', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '50', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '261', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('46', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '759', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '78', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '613', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '137', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '136', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '760', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '109', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('47', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '759', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '413', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '473', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '137', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '375', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '374', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '373', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '760', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '160', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '109', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '118', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('48', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '759', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '137', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '8', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '98', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '760', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '43', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '109', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '6', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '237', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('49', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '594', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '293', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '229', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '54', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '160', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '184', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '142', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '55', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '267', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('50', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '45', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '413', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '473', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '46', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '229', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '136', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '51', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '43', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '226', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '163', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '118', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '176', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '55', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '50', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '261', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('51', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '45', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '253', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '473', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '633', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '46', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '54', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '43', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '226', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '118', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '39', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '38', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '176', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '40', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('52', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '78', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '613', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '54', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '136', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '56', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('53', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '8', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '136', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '43', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '173', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '6', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '237', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('54', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '593', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '355', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '354', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '136', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '43', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '228', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '173', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('55', '129', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '759', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '756', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '414', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '413', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '313', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '140', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '137', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '433', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '594', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '415', '1', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '139', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '315', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '293', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '229', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '769', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '762', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '54', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '98', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '186', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '43', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '165', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '160', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '197', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '109', '300', '300');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '393', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '755', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '184', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '183', '5', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '172', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '164', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '142', '0', '1');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '141', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '138', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '115', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '55', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '333', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '95', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '673', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '182', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '171', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '356', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '202', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '113', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '111', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '44', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '162', '1', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '267', '0', '5');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '185', '0', '0');
INSERT INTO `playercreateinfo_skills` VALUES ('56', '129', '0', '0');

-- ----------------------------
-- Table structure for `playercreateinfo_spells`
-- ----------------------------
DROP TABLE IF EXISTS `playercreateinfo_spells`;
CREATE TABLE `playercreateinfo_spells` (
  `indexid` int(4) NOT NULL DEFAULT '0',
  `spellid` int(5) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playercreateinfo_spells
-- ----------------------------
INSERT INTO `playercreateinfo_spells` VALUES ('1', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '20599');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '20600');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '20597');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '20598');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '20864');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('1', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '20599');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '20600');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '20597');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '20598');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '20864');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '635');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '20154');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '199');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '20599');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '20600');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '20597');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '20598');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '20864');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('18', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '20599');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '20600');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '20597');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '20598');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '20864');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('25', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '20599');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '20600');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '20597');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '20598');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '20864');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '133');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '168');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('34', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '20599');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '20600');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '20597');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '20598');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '20864');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '686');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '687');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('38', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '197');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '21563');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '20572');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '20573');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '20574');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('2', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '20572');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '20573');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '20574');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '20576');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '264');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('11', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '21563');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '20572');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '20573');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '20574');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('19', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '21563');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '20572');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '20573');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '20574');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '331');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '403');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '2161');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '686');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '20572');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '20573');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '20574');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '20575');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '687');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('39', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '197');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '2481');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '20596');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '20595');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '20594');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '672');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('3', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '635');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '20154');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '2481');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '20596');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '20595');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '20594');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '672');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '199');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '2481');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '20596');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '20595');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '20594');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '672');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '266');
INSERT INTO `playercreateinfo_spells` VALUES ('12', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '2481');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '20596');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '20595');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '20594');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '672');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('20', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '2481');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '20596');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '20595');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '20594');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '672');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('26', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '671');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '20580');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '20583');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '20582');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '20585');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '21009');
INSERT INTO `playercreateinfo_spells` VALUES ('4', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '671');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '264');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '20580');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '20583');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '20582');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '20585');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '21009');
INSERT INTO `playercreateinfo_spells` VALUES ('15', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '671');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '20580');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '20583');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '20582');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '20585');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '21009');
INSERT INTO `playercreateinfo_spells` VALUES ('21', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '671');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '20580');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '20583');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '20582');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '20585');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '21009');
INSERT INTO `playercreateinfo_spells` VALUES ('27', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '5176');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '5185');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '671');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '20580');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '20583');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '20582');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '20585');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '21009');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '5227');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '7744');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '20577');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '17737');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '202');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('5', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '5227');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '7744');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '20577');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '17737');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('22', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '5227');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '7744');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '20577');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '17737');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('28', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '5227');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '7744');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '20577');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '133');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '17737');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '168');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('35', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '5227');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '7744');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '20577');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '686');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '687');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '17737');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('40', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '20549');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '20550');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '20551');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '20552');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '670');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '199');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('6', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '20549');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '20550');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '20551');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '20552');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '670');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '266');
INSERT INTO `playercreateinfo_spells` VALUES ('16', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '20549');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '20550');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '20551');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '20552');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '331');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '403');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '670');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '5176');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '20549');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '20550');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '20551');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '20552');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '5185');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '670');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '20589');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '20591');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '20593');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '20592');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '7340');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('7', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '20589');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '20591');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '20593');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '20592');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '7340');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('23', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '133');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '20589');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '20591');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '20593');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '20592');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '168');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '7340');
INSERT INTO `playercreateinfo_spells` VALUES ('36', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '686');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '687');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '20589');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '20591');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '20593');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '20592');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '7340');
INSERT INTO `playercreateinfo_spells` VALUES ('41', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '7341');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '23301');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '20555');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '20557');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '20558');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '26290');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '26296');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('8', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '7341');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '23301');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '20554');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '20555');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '20557');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '20558');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '26290');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '196');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '264');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('17', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '7341');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '23301');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '20555');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '20557');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '20558');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '26290');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '26297');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('24', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '7341');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '23301');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '20554');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '20555');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '20557');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '20558');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '26290');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('29', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '7341');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '331');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '403');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '23301');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '20554');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '20555');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '20557');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '20558');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '26290');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '133');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '7341');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '23301');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '20554');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '20555');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '20557');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '20558');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '26290');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '168');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('37', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('42', '27764');
INSERT INTO `playercreateinfo_spells` VALUES ('43', '27764');
INSERT INTO `playercreateinfo_spells` VALUES ('30', '27763');
INSERT INTO `playercreateinfo_spells` VALUES ('31', '27763');
INSERT INTO `playercreateinfo_spells` VALUES ('32', '27763');
INSERT INTO `playercreateinfo_spells` VALUES ('9', '27762');
INSERT INTO `playercreateinfo_spells` VALUES ('10', '27762');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '29932');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '78');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '2457');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '28875');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '28880');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '202');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '32215');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '5301');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('44', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '29932');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '635');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '20154');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '28875');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '28880');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '199');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '27762');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('45', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '29932');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '28875');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '28880');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '5011');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '34082');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('46', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '29932');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '28878');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '28875');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '28880');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('47', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '29932');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '403');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '331');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '28878');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '28875');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '28880');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '27763');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('48', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '29932');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '133');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '668');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '20579');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '28878');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '28875');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '28880');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '168');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('49', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '28730');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '635');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '20154');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '27762');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '202');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('50', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '28730');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '264');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '2973');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '34082');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '75');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '13358');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '24949');
INSERT INTO `playercreateinfo_spells` VALUES ('51', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '25046');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '2098');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '1752');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '21184');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '2567');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '2764');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '16092');
INSERT INTO `playercreateinfo_spells` VALUES ('52', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '28730');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '198');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '585');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '2050');
INSERT INTO `playercreateinfo_spells` VALUES ('53', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '28730');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '133');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '227');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '168');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('54', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '686');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '28730');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '687');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '5019');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '5009');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '1180');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('55', '203');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '28877');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '822');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '28734');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '28730');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '9077');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '8737');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '813');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '9116');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '9078');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '201');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '669');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '6247');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '6246');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '6233');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '2382');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '8386');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '3050');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '3365');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '7355');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '7267');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '7266');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '2479');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '6603');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '6478');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '6477');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '27762');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '9125');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '21652');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '21651');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '22810');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '22027');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '202');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '522');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '81');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '204');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '107');
INSERT INTO `playercreateinfo_spells` VALUES ('56', '203');

-- ----------------------------
-- Table structure for `playeritems`
-- ----------------------------
DROP TABLE IF EXISTS `playeritems`;
CREATE TABLE `playeritems` (
  `ownerguid` int(10) unsigned NOT NULL DEFAULT '0',
  `guid` bigint(10) unsigned NOT NULL DEFAULT '0',
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `creator` int(10) unsigned NOT NULL DEFAULT '0',
  `count` int(10) unsigned NOT NULL DEFAULT '0',
  `charges` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `randomprop` int(10) unsigned NOT NULL DEFAULT '0',
  `itemtext` int(10) unsigned NOT NULL DEFAULT '0',
  `durability` int(10) unsigned NOT NULL DEFAULT '0',
  `containerslot` int(11) DEFAULT '-1',
  `slot` int(10) NOT NULL DEFAULT '0',
  `enchantments` longtext NOT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `guid` (`guid`),
  KEY `ownerguid` (`ownerguid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playeritems
-- ----------------------------

-- ----------------------------
-- Table structure for `playerpets`
-- ----------------------------
DROP TABLE IF EXISTS `playerpets`;
CREATE TABLE `playerpets` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `petnumber` int(11) NOT NULL DEFAULT '0',
  `name` varchar(21) NOT NULL DEFAULT '',
  `entryid` bigint(20) NOT NULL DEFAULT '0',
  `data` longtext NOT NULL,
  `xp` int(11) NOT NULL DEFAULT '0',
  `active` tinyint(1) NOT NULL DEFAULT '0',
  `level` int(11) NOT NULL DEFAULT '0',
  `loyalty` int(11) NOT NULL DEFAULT '0',
  `actionbar` varchar(200) NOT NULL DEFAULT '',
  `nextloyaltyupdate` int(11) NOT NULL DEFAULT '0',
  `summon` int(11) NOT NULL DEFAULT '0',
  `autocastspell` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playerpets
-- ----------------------------

-- ----------------------------
-- Table structure for `playerpetspells`
-- ----------------------------
DROP TABLE IF EXISTS `playerpetspells`;
CREATE TABLE `playerpetspells` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `petnumber` int(4) NOT NULL DEFAULT '0',
  `spellid` int(4) NOT NULL DEFAULT '0',
  `flags` int(4) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playerpetspells
-- ----------------------------

-- ----------------------------
-- Table structure for `playersummonspells`
-- ----------------------------
DROP TABLE IF EXISTS `playersummonspells`;
CREATE TABLE `playersummonspells` (
  `ownerguid` bigint(20) NOT NULL DEFAULT '0',
  `entryid` int(4) NOT NULL DEFAULT '0',
  `spellid` int(4) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of playersummonspells
-- ----------------------------

-- ----------------------------
-- Table structure for `pvpareas`
-- ----------------------------
DROP TABLE IF EXISTS `pvpareas`;
CREATE TABLE `pvpareas` (
  `AreaID` int(5) NOT NULL DEFAULT '0',
  `AreaName` varchar(255) NOT NULL DEFAULT '',
  `PvPType` int(2) NOT NULL DEFAULT '0',
  PRIMARY KEY (`AreaID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of pvpareas
-- ----------------------------
INSERT INTO `pvpareas` VALUES ('1', 'Dun Morogh', '1');
INSERT INTO `pvpareas` VALUES ('2', 'Longshore', '1');
INSERT INTO `pvpareas` VALUES ('3', 'Badlands', '3');
INSERT INTO `pvpareas` VALUES ('4', 'Blasted Lands', '3');
INSERT INTO `pvpareas` VALUES ('7', 'Blackwater Cove', '3');
INSERT INTO `pvpareas` VALUES ('8', 'Swamp of Sorrows', '3');
INSERT INTO `pvpareas` VALUES ('9', 'Northshire Valley', '1');
INSERT INTO `pvpareas` VALUES ('10', 'Duskwood', '3');
INSERT INTO `pvpareas` VALUES ('11', 'Wetlands', '3');
INSERT INTO `pvpareas` VALUES ('12', 'Elwynn Forest', '1');
INSERT INTO `pvpareas` VALUES ('13', 'The World Tree', '3');
INSERT INTO `pvpareas` VALUES ('14', 'Durotar', '2');
INSERT INTO `pvpareas` VALUES ('15', 'Dustwallow Marsh', '3');
INSERT INTO `pvpareas` VALUES ('16', 'Azshara', '3');
INSERT INTO `pvpareas` VALUES ('17', 'The Barrens', '2');
INSERT INTO `pvpareas` VALUES ('18', 'Crystal Lake', '1');
INSERT INTO `pvpareas` VALUES ('19', 'Zul\'Gurub', '3');
INSERT INTO `pvpareas` VALUES ('20', 'Moonbrook', '1');
INSERT INTO `pvpareas` VALUES ('21', 'Kul Tiras', '0');
INSERT INTO `pvpareas` VALUES ('22', 'Programmer Isle', '0');
INSERT INTO `pvpareas` VALUES ('23', 'Northshire River', '1');
INSERT INTO `pvpareas` VALUES ('24', 'Northshire Abbey', '1');
INSERT INTO `pvpareas` VALUES ('25', 'Blackrock Mountain', '3');
INSERT INTO `pvpareas` VALUES ('26', 'Lighthouse', '1');
INSERT INTO `pvpareas` VALUES ('28', 'Western Plaguelands', '3');
INSERT INTO `pvpareas` VALUES ('30', 'Nine', '3');
INSERT INTO `pvpareas` VALUES ('32', 'The Cemetary', '3');
INSERT INTO `pvpareas` VALUES ('33', 'Stranglethorn Vale', '3');
INSERT INTO `pvpareas` VALUES ('34', 'Echo Ridge Mine', '1');
INSERT INTO `pvpareas` VALUES ('35', 'Booty Bay', '0');
INSERT INTO `pvpareas` VALUES ('36', 'Alterac Mountains', '3');
INSERT INTO `pvpareas` VALUES ('37', 'Lake Nazferiti', '3');
INSERT INTO `pvpareas` VALUES ('38', 'Loch Modan', '1');
INSERT INTO `pvpareas` VALUES ('40', 'Westfall', '1');
INSERT INTO `pvpareas` VALUES ('41', 'Deadwind Pass', '3');
INSERT INTO `pvpareas` VALUES ('42', 'Darkshire', '1');
INSERT INTO `pvpareas` VALUES ('43', 'Wild Shore', '3');
INSERT INTO `pvpareas` VALUES ('44', 'Redridge Mountains', '3');
INSERT INTO `pvpareas` VALUES ('45', 'Arathi Highlands', '3');
INSERT INTO `pvpareas` VALUES ('46', 'Burning Steppes', '3');
INSERT INTO `pvpareas` VALUES ('47', 'The Hinterlands', '3');
INSERT INTO `pvpareas` VALUES ('49', 'Dead Man\'s Hole', '0');
INSERT INTO `pvpareas` VALUES ('51', 'Searing Gorge', '3');
INSERT INTO `pvpareas` VALUES ('53', 'Thieves Camp', '1');
INSERT INTO `pvpareas` VALUES ('54', 'Jasperlode Mine', '1');
INSERT INTO `pvpareas` VALUES ('55', 'Valley of Heroes', '1');
INSERT INTO `pvpareas` VALUES ('56', 'Heroes\' Vigil', '1');
INSERT INTO `pvpareas` VALUES ('57', 'Fargodeep Mine', '1');
INSERT INTO `pvpareas` VALUES ('59', 'Northshire Vineyards', '1');
INSERT INTO `pvpareas` VALUES ('60', 'Forest\'s Edge', '1');
INSERT INTO `pvpareas` VALUES ('61', 'Thunder Falls', '1');
INSERT INTO `pvpareas` VALUES ('62', 'Brackwell Pumpkin Patch', '1');
INSERT INTO `pvpareas` VALUES ('63', 'The Stonefield Farm', '1');
INSERT INTO `pvpareas` VALUES ('64', 'The Maclure Vineyards', '1');
INSERT INTO `pvpareas` VALUES ('65', '***On Map Dungeon***', '0');
INSERT INTO `pvpareas` VALUES ('66', '***On Map Dungeon***', '0');
INSERT INTO `pvpareas` VALUES ('67', '***On Map Dungeon***', '0');
INSERT INTO `pvpareas` VALUES ('68', 'Lake Everstill', '3');
INSERT INTO `pvpareas` VALUES ('69', 'Lakeshire', '3');
INSERT INTO `pvpareas` VALUES ('70', 'Stonewatch', '3');
INSERT INTO `pvpareas` VALUES ('71', 'Stonewatch Falls', '3');
INSERT INTO `pvpareas` VALUES ('72', 'The Dark Portal', '3');
INSERT INTO `pvpareas` VALUES ('73', 'The Tainted Scar', '3');
INSERT INTO `pvpareas` VALUES ('74', 'Pool of Tears', '3');
INSERT INTO `pvpareas` VALUES ('75', 'Stonard', '3');
INSERT INTO `pvpareas` VALUES ('76', 'Fallow Sanctuary', '3');
INSERT INTO `pvpareas` VALUES ('77', 'Anvilmar', '1');
INSERT INTO `pvpareas` VALUES ('80', 'Stormwind Mountains', '1');
INSERT INTO `pvpareas` VALUES ('81', 'Jeff NE Quadrant Changed', '0');
INSERT INTO `pvpareas` VALUES ('82', 'Jeff NW Quadrant', '0');
INSERT INTO `pvpareas` VALUES ('83', 'Jeff SE Quadrant', '0');
INSERT INTO `pvpareas` VALUES ('84', 'Jeff SW Quadrant', '0');
INSERT INTO `pvpareas` VALUES ('85', 'Tirisfal Glades', '2');
INSERT INTO `pvpareas` VALUES ('86', 'Stone Cairn Lake', '1');
INSERT INTO `pvpareas` VALUES ('87', 'Goldshire', '1');
INSERT INTO `pvpareas` VALUES ('88', 'Eastvale Logging Camp', '1');
INSERT INTO `pvpareas` VALUES ('89', 'Mirror Lake Orchard', '1');
INSERT INTO `pvpareas` VALUES ('91', 'Tower of Azora', '1');
INSERT INTO `pvpareas` VALUES ('92', 'Mirror Lake', '1');
INSERT INTO `pvpareas` VALUES ('93', 'Vul\'Gol Ogre Mound', '3');
INSERT INTO `pvpareas` VALUES ('94', 'Raven Hill', '3');
INSERT INTO `pvpareas` VALUES ('95', 'Redridge Canyons', '3');
INSERT INTO `pvpareas` VALUES ('96', 'Tower of Ilgalar', '3');
INSERT INTO `pvpareas` VALUES ('97', 'Alther\'s Mill', '3');
INSERT INTO `pvpareas` VALUES ('98', 'Rethban Caverns', '3');
INSERT INTO `pvpareas` VALUES ('99', 'Rebel Camp', '3');
INSERT INTO `pvpareas` VALUES ('100', 'Nesingwary\'s Expedition', '3');
INSERT INTO `pvpareas` VALUES ('101', 'Kurzen\'s Compound', '3');
INSERT INTO `pvpareas` VALUES ('102', 'Ruins of Zul\'Kunda', '3');
INSERT INTO `pvpareas` VALUES ('103', 'Ruins of Zul\'Mamwe', '3');
INSERT INTO `pvpareas` VALUES ('104', 'The Vile Reef', '3');
INSERT INTO `pvpareas` VALUES ('105', 'Mosh\'Ogg Ogre Mound', '3');
INSERT INTO `pvpareas` VALUES ('106', 'The Stockpile', '3');
INSERT INTO `pvpareas` VALUES ('107', 'Saldean\'s Farm', '1');
INSERT INTO `pvpareas` VALUES ('108', 'Sentinel Hill', '1');
INSERT INTO `pvpareas` VALUES ('109', 'Furlbrow\'s Pumpkin Farm', '1');
INSERT INTO `pvpareas` VALUES ('111', 'Jangolode Mine', '1');
INSERT INTO `pvpareas` VALUES ('113', 'Gold Coast Quarry', '1');
INSERT INTO `pvpareas` VALUES ('115', 'Westfall Lighthouse', '1');
INSERT INTO `pvpareas` VALUES ('116', 'Misty Valley', '3');
INSERT INTO `pvpareas` VALUES ('117', 'Grom\'gol Base Camp', '3');
INSERT INTO `pvpareas` VALUES ('118', 'Whelgar\'s Excavation Site', '3');
INSERT INTO `pvpareas` VALUES ('120', 'Westbrook Garrison', '1');
INSERT INTO `pvpareas` VALUES ('121', 'Tranquil Gardens Cemetery', '3');
INSERT INTO `pvpareas` VALUES ('122', 'Zuuldaia Ruins', '3');
INSERT INTO `pvpareas` VALUES ('123', 'Bal\'lal Ruins', '3');
INSERT INTO `pvpareas` VALUES ('125', 'Kal\'ai Ruins', '3');
INSERT INTO `pvpareas` VALUES ('126', 'Tkashi Ruins', '3');
INSERT INTO `pvpareas` VALUES ('127', 'Balia\'mah Ruins', '3');
INSERT INTO `pvpareas` VALUES ('128', 'Ziata\'jai Ruins', '3');
INSERT INTO `pvpareas` VALUES ('129', 'Mizjah Ruins', '3');
INSERT INTO `pvpareas` VALUES ('130', 'Silverpine Forest', '2');
INSERT INTO `pvpareas` VALUES ('131', 'Kharanos', '1');
INSERT INTO `pvpareas` VALUES ('132', 'Coldridge Valley', '1');
INSERT INTO `pvpareas` VALUES ('133', 'Gnomeregan', '1');
INSERT INTO `pvpareas` VALUES ('134', 'Gol\'Bolar Quarry', '1');
INSERT INTO `pvpareas` VALUES ('135', 'Frostmane Hold', '1');
INSERT INTO `pvpareas` VALUES ('136', 'The Grizzled Den', '1');
INSERT INTO `pvpareas` VALUES ('137', 'Brewnall Village', '1');
INSERT INTO `pvpareas` VALUES ('138', 'Misty Pine Refuge', '1');
INSERT INTO `pvpareas` VALUES ('139', 'Eastern Plaguelands', '3');
INSERT INTO `pvpareas` VALUES ('141', 'Teldrassil', '1');
INSERT INTO `pvpareas` VALUES ('142', 'Ironband\'s Excavation Site', '1');
INSERT INTO `pvpareas` VALUES ('143', 'Mo\'grosh Stronghold', '1');
INSERT INTO `pvpareas` VALUES ('144', 'Thelsamar', '1');
INSERT INTO `pvpareas` VALUES ('145', 'Algaz Gate', '1');
INSERT INTO `pvpareas` VALUES ('146', 'Stonewrought Dam', '1');
INSERT INTO `pvpareas` VALUES ('147', 'The Farstrider Lodge', '1');
INSERT INTO `pvpareas` VALUES ('148', 'Darkshore', '1');
INSERT INTO `pvpareas` VALUES ('149', 'Silver Stream Mine', '1');
INSERT INTO `pvpareas` VALUES ('150', 'Menethil Harbor', '1');
INSERT INTO `pvpareas` VALUES ('151', 'Designer Island', '0');
INSERT INTO `pvpareas` VALUES ('152', 'The Bulwark', '2');
INSERT INTO `pvpareas` VALUES ('153', 'Ruins of Lordaeron', '2');
INSERT INTO `pvpareas` VALUES ('154', 'Deathknell', '2');
INSERT INTO `pvpareas` VALUES ('155', 'Night Web\'s Hollow', '2');
INSERT INTO `pvpareas` VALUES ('156', 'Solliden Farmstead', '2');
INSERT INTO `pvpareas` VALUES ('157', 'Agamand Mills', '2');
INSERT INTO `pvpareas` VALUES ('158', 'Agamand Family Crypt', '2');
INSERT INTO `pvpareas` VALUES ('159', 'Brill', '2');
INSERT INTO `pvpareas` VALUES ('160', 'Whispering Gardens', '2');
INSERT INTO `pvpareas` VALUES ('161', 'Terrace of Repose', '2');
INSERT INTO `pvpareas` VALUES ('162', 'Brightwater Lake', '2');
INSERT INTO `pvpareas` VALUES ('163', 'Gunther\'s Retreat', '2');
INSERT INTO `pvpareas` VALUES ('164', 'Garren\'s Haunt', '2');
INSERT INTO `pvpareas` VALUES ('165', 'Balnir Farmstead', '2');
INSERT INTO `pvpareas` VALUES ('166', 'Cold Hearth Manor', '2');
INSERT INTO `pvpareas` VALUES ('167', 'Crusader Outpost', '2');
INSERT INTO `pvpareas` VALUES ('168', 'The North Coast', '2');
INSERT INTO `pvpareas` VALUES ('169', 'Whispering Shore', '2');
INSERT INTO `pvpareas` VALUES ('170', 'Lordamere Lake', '2');
INSERT INTO `pvpareas` VALUES ('172', 'Fenris Isle', '2');
INSERT INTO `pvpareas` VALUES ('173', 'Faol\'s Rest', '2');
INSERT INTO `pvpareas` VALUES ('186', 'Dolanaar', '1');
INSERT INTO `pvpareas` VALUES ('187', 'Darnassus', '1');
INSERT INTO `pvpareas` VALUES ('188', 'Shadowglen', '1');
INSERT INTO `pvpareas` VALUES ('189', 'Steelgrill\'s Depot', '1');
INSERT INTO `pvpareas` VALUES ('190', 'Hearthglen', '3');
INSERT INTO `pvpareas` VALUES ('192', 'Northridge Lumber Camp', '3');
INSERT INTO `pvpareas` VALUES ('193', 'Ruins of Andorhal', '3');
INSERT INTO `pvpareas` VALUES ('195', 'School of Necromancy', '3');
INSERT INTO `pvpareas` VALUES ('196', 'Uther\'s Tomb', '3');
INSERT INTO `pvpareas` VALUES ('197', 'Sorrow Hill', '3');
INSERT INTO `pvpareas` VALUES ('198', 'The Weeping Cave', '3');
INSERT INTO `pvpareas` VALUES ('199', 'Felstone Field', '3');
INSERT INTO `pvpareas` VALUES ('200', 'Dalson\'s Tears', '3');
INSERT INTO `pvpareas` VALUES ('201', 'Gahrron\'s Withering', '3');
INSERT INTO `pvpareas` VALUES ('202', 'The Writhing Haunt', '3');
INSERT INTO `pvpareas` VALUES ('203', 'Mardenholde Keep', '3');
INSERT INTO `pvpareas` VALUES ('204', 'Pyrewood Village', '2');
INSERT INTO `pvpareas` VALUES ('205', 'Dun Modr', '3');
INSERT INTO `pvpareas` VALUES ('206', 'Westfall', '1');
INSERT INTO `pvpareas` VALUES ('207', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('208', ' Ironcladcove', '0');
INSERT INTO `pvpareas` VALUES ('209', 'Shadowfang Keep', '2');
INSERT INTO `pvpareas` VALUES ('210', '***On Map Dungeon***', '0');
INSERT INTO `pvpareas` VALUES ('211', 'Iceflow Lake', '1');
INSERT INTO `pvpareas` VALUES ('212', 'Helm\'s Bed Lake', '1');
INSERT INTO `pvpareas` VALUES ('213', 'Deep Elem Mine', '2');
INSERT INTO `pvpareas` VALUES ('214', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('215', 'Mulgore', '2');
INSERT INTO `pvpareas` VALUES ('219', 'Alexston Farmstead', '1');
INSERT INTO `pvpareas` VALUES ('220', 'Red Cloud Mesa', '2');
INSERT INTO `pvpareas` VALUES ('221', 'Camp Narache', '2');
INSERT INTO `pvpareas` VALUES ('222', 'Bloodhoof Village', '2');
INSERT INTO `pvpareas` VALUES ('223', 'Stonebull Lake', '2');
INSERT INTO `pvpareas` VALUES ('224', 'Ravaged Caravan', '2');
INSERT INTO `pvpareas` VALUES ('225', 'Red Rocks', '2');
INSERT INTO `pvpareas` VALUES ('226', 'The Skittering Dark', '2');
INSERT INTO `pvpareas` VALUES ('227', 'Valgan\'s Field', '2');
INSERT INTO `pvpareas` VALUES ('228', 'The Sepulcher', '2');
INSERT INTO `pvpareas` VALUES ('229', 'Olsen\'s Farthing', '2');
INSERT INTO `pvpareas` VALUES ('230', 'The Greymane Wall', '2');
INSERT INTO `pvpareas` VALUES ('231', 'Beren\'s Peril', '2');
INSERT INTO `pvpareas` VALUES ('232', 'The Dawning Isles', '2');
INSERT INTO `pvpareas` VALUES ('233', 'Ambermill', '2');
INSERT INTO `pvpareas` VALUES ('235', 'Fenris Keep', '2');
INSERT INTO `pvpareas` VALUES ('236', 'Shadowfang Keep', '2');
INSERT INTO `pvpareas` VALUES ('237', 'The Decrepit Ferry', '2');
INSERT INTO `pvpareas` VALUES ('238', 'Malden\'s Orchard', '2');
INSERT INTO `pvpareas` VALUES ('239', 'The Ivar Patch', '2');
INSERT INTO `pvpareas` VALUES ('240', 'The Dead Field', '2');
INSERT INTO `pvpareas` VALUES ('241', 'The Rotting Orchard', '3');
INSERT INTO `pvpareas` VALUES ('242', 'Brightwood Grove', '3');
INSERT INTO `pvpareas` VALUES ('243', 'Forlorn Rowe', '3');
INSERT INTO `pvpareas` VALUES ('244', 'The Whipple Estate', '3');
INSERT INTO `pvpareas` VALUES ('245', 'The Yorgen Farmstead', '3');
INSERT INTO `pvpareas` VALUES ('246', 'The Cauldron', '3');
INSERT INTO `pvpareas` VALUES ('247', 'Grimesilt Dig Site', '3');
INSERT INTO `pvpareas` VALUES ('249', 'Dreadmaul Rock', '3');
INSERT INTO `pvpareas` VALUES ('250', 'Ruins of Thaurissan', '3');
INSERT INTO `pvpareas` VALUES ('251', 'Flame Crest', '3');
INSERT INTO `pvpareas` VALUES ('252', 'Blackrock Stronghold', '3');
INSERT INTO `pvpareas` VALUES ('253', 'The Pillar of Ash', '3');
INSERT INTO `pvpareas` VALUES ('254', 'Blackrock Mountain', '3');
INSERT INTO `pvpareas` VALUES ('255', 'Altar of Storms', '3');
INSERT INTO `pvpareas` VALUES ('256', 'Aldrassil', '1');
INSERT INTO `pvpareas` VALUES ('257', 'Shadowthread Cave', '1');
INSERT INTO `pvpareas` VALUES ('258', 'Fel Rock', '1');
INSERT INTO `pvpareas` VALUES ('259', 'Lake Al\'Ameth', '1');
INSERT INTO `pvpareas` VALUES ('260', 'Starbreeze Village', '1');
INSERT INTO `pvpareas` VALUES ('261', 'Gnarlpine Hold', '1');
INSERT INTO `pvpareas` VALUES ('262', 'Ban\'ethil Barrow Den', '1');
INSERT INTO `pvpareas` VALUES ('263', 'The Cleft', '1');
INSERT INTO `pvpareas` VALUES ('264', 'The Oracle Glade', '1');
INSERT INTO `pvpareas` VALUES ('265', 'Wellspring River', '1');
INSERT INTO `pvpareas` VALUES ('266', 'Wellspring Lake', '1');
INSERT INTO `pvpareas` VALUES ('267', 'Hillsbrad Foothills', '3');
INSERT INTO `pvpareas` VALUES ('268', 'Azshara Crater', '3');
INSERT INTO `pvpareas` VALUES ('269', 'Dun Algaz', '1');
INSERT INTO `pvpareas` VALUES ('271', 'Southshore', '3');
INSERT INTO `pvpareas` VALUES ('272', 'Tarren Mill', '3');
INSERT INTO `pvpareas` VALUES ('275', 'Durnholde Keep', '3');
INSERT INTO `pvpareas` VALUES ('276', ' Stonewrought Pass', '3');
INSERT INTO `pvpareas` VALUES ('277', 'The Foothill Caverns', '3');
INSERT INTO `pvpareas` VALUES ('278', 'Lordamere Internment Camp', '3');
INSERT INTO `pvpareas` VALUES ('279', 'Dalaran', '3');
INSERT INTO `pvpareas` VALUES ('280', 'Strahnbrad', '3');
INSERT INTO `pvpareas` VALUES ('281', 'Ruins of Alterac', '3');
INSERT INTO `pvpareas` VALUES ('282', 'Crushridge Hold', '3');
INSERT INTO `pvpareas` VALUES ('283', 'Slaughter Hollow', '3');
INSERT INTO `pvpareas` VALUES ('284', 'The Uplands', '3');
INSERT INTO `pvpareas` VALUES ('285', 'Southpoint Tower', '3');
INSERT INTO `pvpareas` VALUES ('286', 'Hillsbrad Fields', '3');
INSERT INTO `pvpareas` VALUES ('287', 'Hillsbrad', '3');
INSERT INTO `pvpareas` VALUES ('288', 'Azurelode Mine', '3');
INSERT INTO `pvpareas` VALUES ('289', 'Nethander Stead', '3');
INSERT INTO `pvpareas` VALUES ('290', 'Dun Garok', '3');
INSERT INTO `pvpareas` VALUES ('293', 'Thoradin\'s Wall', '3');
INSERT INTO `pvpareas` VALUES ('294', 'Eastern Strand', '3');
INSERT INTO `pvpareas` VALUES ('295', 'Western Strand', '3');
INSERT INTO `pvpareas` VALUES ('296', 'South Seas', '3');
INSERT INTO `pvpareas` VALUES ('297', 'Jaguero Isle', '3');
INSERT INTO `pvpareas` VALUES ('298', 'Baradin Bay', '3');
INSERT INTO `pvpareas` VALUES ('299', 'Menethil Bay', '3');
INSERT INTO `pvpareas` VALUES ('300', 'Misty Reed Strand', '3');
INSERT INTO `pvpareas` VALUES ('301', 'The Savage Coast', '3');
INSERT INTO `pvpareas` VALUES ('302', 'The Crystal Shore', '3');
INSERT INTO `pvpareas` VALUES ('303', 'Shell Beach', '3');
INSERT INTO `pvpareas` VALUES ('305', 'North Tide\'s Run', '2');
INSERT INTO `pvpareas` VALUES ('306', 'South Tide\'s Run', '2');
INSERT INTO `pvpareas` VALUES ('307', 'The Overlook Cliffs', '3');
INSERT INTO `pvpareas` VALUES ('308', 'The Forbidding Sea', '3');
INSERT INTO `pvpareas` VALUES ('309', 'Ironbeard\'s Tomb', '3');
INSERT INTO `pvpareas` VALUES ('310', 'Crystalvein Mine', '3');
INSERT INTO `pvpareas` VALUES ('311', 'Ruins of Aboraz', '3');
INSERT INTO `pvpareas` VALUES ('312', 'Janeiro\'s Point', '3');
INSERT INTO `pvpareas` VALUES ('313', 'Northfold Manor', '3');
INSERT INTO `pvpareas` VALUES ('314', 'Go\'Shek Farm', '3');
INSERT INTO `pvpareas` VALUES ('315', 'Dabyrie\'s Farmstead', '3');
INSERT INTO `pvpareas` VALUES ('316', 'Boulderfist Hall', '3');
INSERT INTO `pvpareas` VALUES ('317', 'Witherbark Village', '3');
INSERT INTO `pvpareas` VALUES ('318', 'Drywhisker Gorge', '3');
INSERT INTO `pvpareas` VALUES ('320', 'Refuge Pointe', '3');
INSERT INTO `pvpareas` VALUES ('321', 'Hammerfall', '3');
INSERT INTO `pvpareas` VALUES ('322', 'Blackwater Shipwrecks', '3');
INSERT INTO `pvpareas` VALUES ('323', 'O\'Breen\'s Camp', '3');
INSERT INTO `pvpareas` VALUES ('324', 'Stromgarde Keep', '3');
INSERT INTO `pvpareas` VALUES ('325', 'The Tower of Arathor', '3');
INSERT INTO `pvpareas` VALUES ('326', 'The Sanctum', '3');
INSERT INTO `pvpareas` VALUES ('327', 'Faldir\'s Cove', '3');
INSERT INTO `pvpareas` VALUES ('328', 'The Drowned Reef', '3');
INSERT INTO `pvpareas` VALUES ('330', 'Thandol Span', '3');
INSERT INTO `pvpareas` VALUES ('331', 'Ashenvale', '3');
INSERT INTO `pvpareas` VALUES ('332', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('333', 'Circle of East Binding', '3');
INSERT INTO `pvpareas` VALUES ('334', 'Circle of West Binding', '3');
INSERT INTO `pvpareas` VALUES ('335', 'Circle of Inner Binding', '3');
INSERT INTO `pvpareas` VALUES ('336', 'Circle of Outer Binding', '3');
INSERT INTO `pvpareas` VALUES ('337', 'Apocryphan\'s Rest', '3');
INSERT INTO `pvpareas` VALUES ('338', 'Angor Fortress', '3');
INSERT INTO `pvpareas` VALUES ('339', 'Lethlor Ravine', '3');
INSERT INTO `pvpareas` VALUES ('340', 'Kargath', '3');
INSERT INTO `pvpareas` VALUES ('341', 'Camp Kosh', '3');
INSERT INTO `pvpareas` VALUES ('342', 'Camp Boff', '3');
INSERT INTO `pvpareas` VALUES ('343', 'Camp Wurg', '3');
INSERT INTO `pvpareas` VALUES ('344', 'Camp Cagg', '3');
INSERT INTO `pvpareas` VALUES ('345', 'Agmond\'s End', '3');
INSERT INTO `pvpareas` VALUES ('346', 'Hammertoe\'s Digsite', '3');
INSERT INTO `pvpareas` VALUES ('347', 'Dustbelch Grotto', '3');
INSERT INTO `pvpareas` VALUES ('348', 'Aerie Peak', '3');
INSERT INTO `pvpareas` VALUES ('349', 'Wildhammer Keep', '3');
INSERT INTO `pvpareas` VALUES ('350', 'Quel\'Danil Lodge', '3');
INSERT INTO `pvpareas` VALUES ('351', 'Skulk Rock', '3');
INSERT INTO `pvpareas` VALUES ('352', 'Zun\'watha', '3');
INSERT INTO `pvpareas` VALUES ('353', 'Shadra\'Alor', '3');
INSERT INTO `pvpareas` VALUES ('354', 'Jintha\'Alor', '3');
INSERT INTO `pvpareas` VALUES ('355', 'The Altar of Zul', '3');
INSERT INTO `pvpareas` VALUES ('356', 'Seradane', '3');
INSERT INTO `pvpareas` VALUES ('357', 'Feralas', '3');
INSERT INTO `pvpareas` VALUES ('358', 'Brambleblade Ravine', '2');
INSERT INTO `pvpareas` VALUES ('359', 'Bael Modan', '2');
INSERT INTO `pvpareas` VALUES ('360', 'The Venture Co. Mine', '2');
INSERT INTO `pvpareas` VALUES ('361', 'Felwood', '3');
INSERT INTO `pvpareas` VALUES ('362', 'Razor Hill', '2');
INSERT INTO `pvpareas` VALUES ('363', 'Valley of Trials', '2');
INSERT INTO `pvpareas` VALUES ('364', 'The Den', '2');
INSERT INTO `pvpareas` VALUES ('365', 'Burning Blade Coven', '2');
INSERT INTO `pvpareas` VALUES ('366', 'Kolkar Crag', '2');
INSERT INTO `pvpareas` VALUES ('367', 'Sen\'jin Village', '2');
INSERT INTO `pvpareas` VALUES ('368', 'Echo Isles', '2');
INSERT INTO `pvpareas` VALUES ('369', 'Thunder Ridge', '2');
INSERT INTO `pvpareas` VALUES ('370', 'Drygulch Ravine', '2');
INSERT INTO `pvpareas` VALUES ('371', 'Dustwind Cave', '2');
INSERT INTO `pvpareas` VALUES ('372', 'Tiragarde Keep', '2');
INSERT INTO `pvpareas` VALUES ('373', 'Scuttle Coast', '2');
INSERT INTO `pvpareas` VALUES ('374', 'Bladefist Bay', '2');
INSERT INTO `pvpareas` VALUES ('375', 'Deadeye Shore', '2');
INSERT INTO `pvpareas` VALUES ('377', 'Southfury River', '2');
INSERT INTO `pvpareas` VALUES ('378', 'Camp Taurajo', '2');
INSERT INTO `pvpareas` VALUES ('379', 'Far Watch Post', '2');
INSERT INTO `pvpareas` VALUES ('380', 'The Crossroads', '2');
INSERT INTO `pvpareas` VALUES ('381', 'Boulder Lode Mine', '2');
INSERT INTO `pvpareas` VALUES ('382', 'The Sludge Fen', '2');
INSERT INTO `pvpareas` VALUES ('383', 'The Dry Hills', '2');
INSERT INTO `pvpareas` VALUES ('384', 'Dreadmist Peak', '2');
INSERT INTO `pvpareas` VALUES ('385', 'Northwatch Hold', '2');
INSERT INTO `pvpareas` VALUES ('386', 'The Forgotten Pools', '2');
INSERT INTO `pvpareas` VALUES ('387', 'Lushwater Oasis', '2');
INSERT INTO `pvpareas` VALUES ('388', 'The Stagnant Oasis', '2');
INSERT INTO `pvpareas` VALUES ('390', 'Field of Giants', '2');
INSERT INTO `pvpareas` VALUES ('391', 'The Merchant Coast', '2');
INSERT INTO `pvpareas` VALUES ('392', 'Ratchet', '2');
INSERT INTO `pvpareas` VALUES ('393', 'Darkspear Strand', '2');
INSERT INTO `pvpareas` VALUES ('394', 'Darrowmere Lake', '3');
INSERT INTO `pvpareas` VALUES ('395', 'Caer Darrow', '3');
INSERT INTO `pvpareas` VALUES ('396', 'Winterhoof Water Well', '2');
INSERT INTO `pvpareas` VALUES ('397', 'Thunderhorn Water Well', '2');
INSERT INTO `pvpareas` VALUES ('398', 'Wildmane Water Well', '2');
INSERT INTO `pvpareas` VALUES ('399', 'Skyline Ridge', '2');
INSERT INTO `pvpareas` VALUES ('400', 'Thousand Needles', '3');
INSERT INTO `pvpareas` VALUES ('401', 'The Tidus Stair', '2');
INSERT INTO `pvpareas` VALUES ('403', 'Shady Rest Inn', '3');
INSERT INTO `pvpareas` VALUES ('404', 'Bael\'dun Digsite', '2');
INSERT INTO `pvpareas` VALUES ('405', 'Desolace', '3');
INSERT INTO `pvpareas` VALUES ('406', 'Stonetalon Mountains', '3');
INSERT INTO `pvpareas` VALUES ('407', 'Orgrimmar', '1');
INSERT INTO `pvpareas` VALUES ('408', 'Gillijim\'s Isle', '0');
INSERT INTO `pvpareas` VALUES ('409', 'Island of Doctor Lapidis', '0');
INSERT INTO `pvpareas` VALUES ('410', 'Razorwind Canyon', '2');
INSERT INTO `pvpareas` VALUES ('411', 'Bathran\'s Haunt', '3');
INSERT INTO `pvpareas` VALUES ('412', 'The Ruins of Ordil\'Aran', '3');
INSERT INTO `pvpareas` VALUES ('413', 'Maestra\'s Post', '3');
INSERT INTO `pvpareas` VALUES ('414', 'The Zoram Strand', '3');
INSERT INTO `pvpareas` VALUES ('415', 'Astranaar', '3');
INSERT INTO `pvpareas` VALUES ('416', 'The Shrine of Aessina', '3');
INSERT INTO `pvpareas` VALUES ('417', 'Fire Scar Shrine', '3');
INSERT INTO `pvpareas` VALUES ('418', 'The Ruins of Stardust', '3');
INSERT INTO `pvpareas` VALUES ('419', 'The Howling Vale', '3');
INSERT INTO `pvpareas` VALUES ('420', 'Silverwind Refuge', '3');
INSERT INTO `pvpareas` VALUES ('421', 'Mystral Lake', '3');
INSERT INTO `pvpareas` VALUES ('422', 'Fallen Sky Lake', '3');
INSERT INTO `pvpareas` VALUES ('424', 'Iris Lake', '3');
INSERT INTO `pvpareas` VALUES ('425', 'Moonwell', '3');
INSERT INTO `pvpareas` VALUES ('426', 'Raynewood Retreat', '3');
INSERT INTO `pvpareas` VALUES ('427', 'The Shady Nook', '3');
INSERT INTO `pvpareas` VALUES ('428', 'Night Run', '3');
INSERT INTO `pvpareas` VALUES ('429', 'Xavian', '3');
INSERT INTO `pvpareas` VALUES ('430', 'Satyrnaar', '3');
INSERT INTO `pvpareas` VALUES ('431', 'Splintertree Post', '3');
INSERT INTO `pvpareas` VALUES ('432', 'The Dor\'Danil Barrow Den', '3');
INSERT INTO `pvpareas` VALUES ('433', 'Falfarren River', '3');
INSERT INTO `pvpareas` VALUES ('434', 'Felfire Hill', '3');
INSERT INTO `pvpareas` VALUES ('435', 'Demon Fall Canyon', '3');
INSERT INTO `pvpareas` VALUES ('436', 'Demon Fall Ridge', '3');
INSERT INTO `pvpareas` VALUES ('437', 'Warsong Lumber Camp', '3');
INSERT INTO `pvpareas` VALUES ('438', 'Bough Shadow', '3');
INSERT INTO `pvpareas` VALUES ('439', 'The Shimmering Flats', '3');
INSERT INTO `pvpareas` VALUES ('440', 'Tanaris', '3');
INSERT INTO `pvpareas` VALUES ('441', 'Lake Falathim', '3');
INSERT INTO `pvpareas` VALUES ('442', 'Auberdine', '1');
INSERT INTO `pvpareas` VALUES ('443', 'Ruins of Mathystra', '1');
INSERT INTO `pvpareas` VALUES ('444', 'Tower of Althalaxx', '1');
INSERT INTO `pvpareas` VALUES ('445', 'Cliffspring Falls', '1');
INSERT INTO `pvpareas` VALUES ('446', 'Bashal\'Aran', '1');
INSERT INTO `pvpareas` VALUES ('447', 'Ameth\'Aran', '1');
INSERT INTO `pvpareas` VALUES ('448', 'Grove of the Ancients', '1');
INSERT INTO `pvpareas` VALUES ('449', 'The Master\'s Glaive', '1');
INSERT INTO `pvpareas` VALUES ('450', 'Remtravel\'s Excavation', '1');
INSERT INTO `pvpareas` VALUES ('452', 'Mist\'s Edge', '1');
INSERT INTO `pvpareas` VALUES ('453', 'The Long Wash', '1');
INSERT INTO `pvpareas` VALUES ('454', 'Wildbend River', '1');
INSERT INTO `pvpareas` VALUES ('455', 'Blackwood Den', '1');
INSERT INTO `pvpareas` VALUES ('456', 'Cliffspring River', '1');
INSERT INTO `pvpareas` VALUES ('457', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('458', 'Gold Road', '2');
INSERT INTO `pvpareas` VALUES ('459', 'Scarlet Watch Post', '2');
INSERT INTO `pvpareas` VALUES ('460', 'Sun Rock Retreat', '3');
INSERT INTO `pvpareas` VALUES ('461', 'Windshear Crag', '3');
INSERT INTO `pvpareas` VALUES ('463', 'Cragpool Lake', '3');
INSERT INTO `pvpareas` VALUES ('464', 'Mirkfallon Lake', '3');
INSERT INTO `pvpareas` VALUES ('465', 'The Charred Vale', '3');
INSERT INTO `pvpareas` VALUES ('466', 'Valley of the Bloodfuries', '3');
INSERT INTO `pvpareas` VALUES ('467', 'Stonetalon Peak', '3');
INSERT INTO `pvpareas` VALUES ('468', 'The Talon Den', '3');
INSERT INTO `pvpareas` VALUES ('469', 'Greatwood Vale', '3');
INSERT INTO `pvpareas` VALUES ('470', 'Thunder Bluff', '2');
INSERT INTO `pvpareas` VALUES ('471', 'Brave Wind Mesa', '2');
INSERT INTO `pvpareas` VALUES ('472', 'Fire Stone Mesa', '2');
INSERT INTO `pvpareas` VALUES ('473', 'Mantle Rock', '2');
INSERT INTO `pvpareas` VALUES ('474', 'Hunter Rise', '2');
INSERT INTO `pvpareas` VALUES ('475', 'Spirit Rise', '2');
INSERT INTO `pvpareas` VALUES ('476', 'Elder Rise', '2');
INSERT INTO `pvpareas` VALUES ('477', 'Ruins of Jubuwal', '3');
INSERT INTO `pvpareas` VALUES ('478', 'Pools of Arlithrien', '1');
INSERT INTO `pvpareas` VALUES ('479', 'The Rustmaul Dig Site', '3');
INSERT INTO `pvpareas` VALUES ('480', 'Camp E\'thok', '3');
INSERT INTO `pvpareas` VALUES ('481', 'Splithoof Crag', '3');
INSERT INTO `pvpareas` VALUES ('482', 'Highperch', '3');
INSERT INTO `pvpareas` VALUES ('483', 'The Screeching Canyon', '3');
INSERT INTO `pvpareas` VALUES ('484', 'Freewind Post', '3');
INSERT INTO `pvpareas` VALUES ('485', 'The Great Lift', '3');
INSERT INTO `pvpareas` VALUES ('486', 'Galak Hold', '3');
INSERT INTO `pvpareas` VALUES ('487', 'Roguefeather Den', '3');
INSERT INTO `pvpareas` VALUES ('488', 'The Weathered Nook', '3');
INSERT INTO `pvpareas` VALUES ('489', 'Thalanaar', '3');
INSERT INTO `pvpareas` VALUES ('490', 'Un\'Goro Crater', '3');
INSERT INTO `pvpareas` VALUES ('491', 'Razorfen Kraul', '3');
INSERT INTO `pvpareas` VALUES ('492', 'Raven Hill Cemetery', '3');
INSERT INTO `pvpareas` VALUES ('493', 'Moonglade', '3');
INSERT INTO `pvpareas` VALUES ('495', 'DELETE ME', '0');
INSERT INTO `pvpareas` VALUES ('496', 'Brackenwall Village', '3');
INSERT INTO `pvpareas` VALUES ('497', 'Swamplight Manor', '3');
INSERT INTO `pvpareas` VALUES ('498', 'Bloodfen Burrow', '3');
INSERT INTO `pvpareas` VALUES ('499', 'Darkmist Cavern', '3');
INSERT INTO `pvpareas` VALUES ('500', 'Moggle Point', '3');
INSERT INTO `pvpareas` VALUES ('501', 'Beezil\'s Wreck', '3');
INSERT INTO `pvpareas` VALUES ('502', 'Witch Hill', '3');
INSERT INTO `pvpareas` VALUES ('503', 'Sentry Point', '3');
INSERT INTO `pvpareas` VALUES ('504', 'North Point Tower', '3');
INSERT INTO `pvpareas` VALUES ('505', 'West Point Tower', '3');
INSERT INTO `pvpareas` VALUES ('506', 'Lost Point', '3');
INSERT INTO `pvpareas` VALUES ('507', 'Bluefen', '3');
INSERT INTO `pvpareas` VALUES ('508', 'Stonemaul Ruins', '3');
INSERT INTO `pvpareas` VALUES ('509', 'The Den of Flame', '3');
INSERT INTO `pvpareas` VALUES ('510', 'The Dragonmurk', '3');
INSERT INTO `pvpareas` VALUES ('511', 'Wyrmbog', '3');
INSERT INTO `pvpareas` VALUES ('512', 'Onyxia\'s Lair', '3');
INSERT INTO `pvpareas` VALUES ('513', 'Theramore Isle', '3');
INSERT INTO `pvpareas` VALUES ('514', 'Foothold Citadel', '3');
INSERT INTO `pvpareas` VALUES ('515', 'Ironclad Prison', '3');
INSERT INTO `pvpareas` VALUES ('516', 'Dustwallow Bay', '3');
INSERT INTO `pvpareas` VALUES ('517', 'Tidefury Cove', '3');
INSERT INTO `pvpareas` VALUES ('518', 'Dreadmurk Shore', '3');
INSERT INTO `pvpareas` VALUES ('536', 'Addle\'s Stead', '3');
INSERT INTO `pvpareas` VALUES ('537', 'Fire Plume Ridge', '3');
INSERT INTO `pvpareas` VALUES ('538', 'Lakkari Tar Pits', '3');
INSERT INTO `pvpareas` VALUES ('539', 'Terror Run', '3');
INSERT INTO `pvpareas` VALUES ('540', 'The Slithering Scar', '3');
INSERT INTO `pvpareas` VALUES ('541', 'Marshal\'s Refuge', '3');
INSERT INTO `pvpareas` VALUES ('542', 'Fungal Rock', '3');
INSERT INTO `pvpareas` VALUES ('543', 'Golakka Hot Springs', '3');
INSERT INTO `pvpareas` VALUES ('556', 'The Loch', '1');
INSERT INTO `pvpareas` VALUES ('576', 'Beggar\'s Haunt', '3');
INSERT INTO `pvpareas` VALUES ('596', 'Kodo Graveyard', '3');
INSERT INTO `pvpareas` VALUES ('597', 'Ghost Walker Post', '3');
INSERT INTO `pvpareas` VALUES ('598', 'Sar\'theris Strand', '3');
INSERT INTO `pvpareas` VALUES ('599', 'Thunder Axe Fortress', '3');
INSERT INTO `pvpareas` VALUES ('600', 'Bolgan\'s Hole', '3');
INSERT INTO `pvpareas` VALUES ('602', 'Mannoroc Coven', '3');
INSERT INTO `pvpareas` VALUES ('603', 'Sargeron', '3');
INSERT INTO `pvpareas` VALUES ('604', 'Magram Village', '3');
INSERT INTO `pvpareas` VALUES ('606', 'Gelkis Village', '3');
INSERT INTO `pvpareas` VALUES ('607', 'Valley of Spears', '3');
INSERT INTO `pvpareas` VALUES ('608', 'Nijel\'s Point', '3');
INSERT INTO `pvpareas` VALUES ('609', 'Kolkar Village', '3');
INSERT INTO `pvpareas` VALUES ('616', 'Hyjal', '3');
INSERT INTO `pvpareas` VALUES ('618', 'Winterspring', '3');
INSERT INTO `pvpareas` VALUES ('636', 'Blackwolf River', '3');
INSERT INTO `pvpareas` VALUES ('637', 'Kodo Rock', '2');
INSERT INTO `pvpareas` VALUES ('638', 'Hidden Path', '2');
INSERT INTO `pvpareas` VALUES ('639', 'Spirit Rock', '2');
INSERT INTO `pvpareas` VALUES ('640', 'Shrine of the Dormant Flame', '2');
INSERT INTO `pvpareas` VALUES ('656', 'Lake Elune\'ara', '3');
INSERT INTO `pvpareas` VALUES ('657', 'The Harborage', '3');
INSERT INTO `pvpareas` VALUES ('676', 'Outland', '3');
INSERT INTO `pvpareas` VALUES ('696', 'Craftsmen\'s Terrace', '1');
INSERT INTO `pvpareas` VALUES ('697', 'Tradesmen\'s Terrace', '1');
INSERT INTO `pvpareas` VALUES ('698', 'The Temple Gardens', '1');
INSERT INTO `pvpareas` VALUES ('699', 'Temple of Elune', '1');
INSERT INTO `pvpareas` VALUES ('700', 'Cenarion Enclave', '1');
INSERT INTO `pvpareas` VALUES ('701', 'Warrior\'s Terrace', '1');
INSERT INTO `pvpareas` VALUES ('702', 'Rut\'theran Village', '1');
INSERT INTO `pvpareas` VALUES ('716', 'Ironband\'s Compound', '1');
INSERT INTO `pvpareas` VALUES ('717', 'The Stockade', '1');
INSERT INTO `pvpareas` VALUES ('718', 'Wailing Caverns', '2');
INSERT INTO `pvpareas` VALUES ('719', 'Blackfathom Deeps', '3');
INSERT INTO `pvpareas` VALUES ('720', 'Fray Island', '2');
INSERT INTO `pvpareas` VALUES ('721', 'Gnomeregan', '1');
INSERT INTO `pvpareas` VALUES ('722', 'Razorfen Downs', '3');
INSERT INTO `pvpareas` VALUES ('736', 'Ban\'ethil Hollow', '1');
INSERT INTO `pvpareas` VALUES ('796', 'Scarlet Monastery', '2');
INSERT INTO `pvpareas` VALUES ('797', 'Jerod\'s Landing', '1');
INSERT INTO `pvpareas` VALUES ('798', 'Ridgepoint Tower', '1');
INSERT INTO `pvpareas` VALUES ('799', 'The Darkened Bank', '3');
INSERT INTO `pvpareas` VALUES ('800', 'Coldridge Pass', '1');
INSERT INTO `pvpareas` VALUES ('801', 'Chill Breeze Valley', '1');
INSERT INTO `pvpareas` VALUES ('802', 'Shimmer Ridge', '1');
INSERT INTO `pvpareas` VALUES ('803', 'Amberstill Ranch', '1');
INSERT INTO `pvpareas` VALUES ('804', 'The Tundrid Hills', '1');
INSERT INTO `pvpareas` VALUES ('805', 'South Gate Pass', '1');
INSERT INTO `pvpareas` VALUES ('806', 'South Gate Outpost', '1');
INSERT INTO `pvpareas` VALUES ('807', 'North Gate Pass', '1');
INSERT INTO `pvpareas` VALUES ('808', 'North Gate Outpost', '1');
INSERT INTO `pvpareas` VALUES ('809', 'Gates of Ironforge', '1');
INSERT INTO `pvpareas` VALUES ('810', 'Stillwater Pond', '2');
INSERT INTO `pvpareas` VALUES ('811', 'Nightmare Vale', '2');
INSERT INTO `pvpareas` VALUES ('812', 'Venomweb Vale', '2');
INSERT INTO `pvpareas` VALUES ('813', 'The Bulwark', '3');
INSERT INTO `pvpareas` VALUES ('814', 'Southfury River', '2');
INSERT INTO `pvpareas` VALUES ('815', 'Southfury River', '2');
INSERT INTO `pvpareas` VALUES ('816', 'Razormane Grounds', '2');
INSERT INTO `pvpareas` VALUES ('817', 'Skull Rock', '2');
INSERT INTO `pvpareas` VALUES ('818', 'Palemane Rock', '2');
INSERT INTO `pvpareas` VALUES ('819', 'Windfury Ridge', '2');
INSERT INTO `pvpareas` VALUES ('820', 'The Golden Plains', '2');
INSERT INTO `pvpareas` VALUES ('821', 'The Rolling Plains', '2');
INSERT INTO `pvpareas` VALUES ('836', 'Dun Algaz', '1');
INSERT INTO `pvpareas` VALUES ('837', 'Dun Algaz', '1');
INSERT INTO `pvpareas` VALUES ('838', 'North Gate Pass', '1');
INSERT INTO `pvpareas` VALUES ('839', 'South Gate Pass', '1');
INSERT INTO `pvpareas` VALUES ('856', 'Twilight Grove', '3');
INSERT INTO `pvpareas` VALUES ('876', 'GM Island', '0');
INSERT INTO `pvpareas` VALUES ('877', 'Delete ME', '0');
INSERT INTO `pvpareas` VALUES ('878', 'Southfury River', '2');
INSERT INTO `pvpareas` VALUES ('879', 'Southfury River', '2');
INSERT INTO `pvpareas` VALUES ('880', 'Thandol Span', '3');
INSERT INTO `pvpareas` VALUES ('881', 'Thandol Span', '3');
INSERT INTO `pvpareas` VALUES ('896', 'Purgation Isle', '3');
INSERT INTO `pvpareas` VALUES ('916', 'The Jansen Stead', '1');
INSERT INTO `pvpareas` VALUES ('917', 'The Dead Acre', '1');
INSERT INTO `pvpareas` VALUES ('918', 'The Molsen Farm', '1');
INSERT INTO `pvpareas` VALUES ('919', 'Stendel\'s Pond', '1');
INSERT INTO `pvpareas` VALUES ('920', 'The Dagger Hills', '1');
INSERT INTO `pvpareas` VALUES ('921', 'Demont\'s Place', '1');
INSERT INTO `pvpareas` VALUES ('922', 'The Dust Plains', '1');
INSERT INTO `pvpareas` VALUES ('923', 'Stonesplinter Valley', '1');
INSERT INTO `pvpareas` VALUES ('924', 'Valley of Kings', '1');
INSERT INTO `pvpareas` VALUES ('925', 'Algaz Station', '1');
INSERT INTO `pvpareas` VALUES ('926', 'Bucklebree Farm', '2');
INSERT INTO `pvpareas` VALUES ('927', 'The Shining Strand', '2');
INSERT INTO `pvpareas` VALUES ('928', 'North Tide\'s Hollow', '2');
INSERT INTO `pvpareas` VALUES ('936', 'Grizzlepaw Ridge', '1');
INSERT INTO `pvpareas` VALUES ('956', 'The Verdant Fields', '0');
INSERT INTO `pvpareas` VALUES ('976', 'Gadgetzan', '0');
INSERT INTO `pvpareas` VALUES ('977', 'Steamwheedle Port', '3');
INSERT INTO `pvpareas` VALUES ('978', 'Zul\'Farrak', '3');
INSERT INTO `pvpareas` VALUES ('979', 'Sandsorrow Watch', '3');
INSERT INTO `pvpareas` VALUES ('980', 'Thistleshrub Valley', '3');
INSERT INTO `pvpareas` VALUES ('981', 'The Gaping Chasm', '3');
INSERT INTO `pvpareas` VALUES ('982', 'The Noxious Lair', '3');
INSERT INTO `pvpareas` VALUES ('983', 'Dunemaul Compound', '3');
INSERT INTO `pvpareas` VALUES ('984', 'Eastmoon Ruins', '3');
INSERT INTO `pvpareas` VALUES ('985', 'Waterspring Field', '3');
INSERT INTO `pvpareas` VALUES ('986', 'Zalashji\'s Den', '3');
INSERT INTO `pvpareas` VALUES ('987', 'Land\'s End Beach', '3');
INSERT INTO `pvpareas` VALUES ('988', 'Wavestrider Beach', '3');
INSERT INTO `pvpareas` VALUES ('989', 'Uldum', '3');
INSERT INTO `pvpareas` VALUES ('990', 'Valley of the Watchers', '3');
INSERT INTO `pvpareas` VALUES ('991', 'Gunstan\'s Post', '3');
INSERT INTO `pvpareas` VALUES ('992', 'Southmoon Ruins', '3');
INSERT INTO `pvpareas` VALUES ('996', 'Render\'s Camp', '3');
INSERT INTO `pvpareas` VALUES ('997', 'Render\'s Valley', '3');
INSERT INTO `pvpareas` VALUES ('998', 'Render\'s Rock', '3');
INSERT INTO `pvpareas` VALUES ('999', 'Stonewatch Tower', '3');
INSERT INTO `pvpareas` VALUES ('1000', 'Galardell Valley', '3');
INSERT INTO `pvpareas` VALUES ('1001', 'Lakeridge Highway', '3');
INSERT INTO `pvpareas` VALUES ('1002', 'Three Corners', '3');
INSERT INTO `pvpareas` VALUES ('1016', 'Direforge Hill', '3');
INSERT INTO `pvpareas` VALUES ('1017', 'Raptor Ridge', '3');
INSERT INTO `pvpareas` VALUES ('1018', 'Black Channel Marsh', '3');
INSERT INTO `pvpareas` VALUES ('1019', 'The Green Belt', '3');
INSERT INTO `pvpareas` VALUES ('1020', 'Mosshide Fen', '3');
INSERT INTO `pvpareas` VALUES ('1021', 'Thelgen Rock', '3');
INSERT INTO `pvpareas` VALUES ('1022', 'Bluegill Marsh', '3');
INSERT INTO `pvpareas` VALUES ('1023', 'Saltspray Glen', '3');
INSERT INTO `pvpareas` VALUES ('1024', 'Sundown Marsh', '3');
INSERT INTO `pvpareas` VALUES ('1025', 'The Green Belt', '3');
INSERT INTO `pvpareas` VALUES ('1036', 'Angerfang Encampment', '3');
INSERT INTO `pvpareas` VALUES ('1037', 'Grim Batol', '3');
INSERT INTO `pvpareas` VALUES ('1038', 'Dragonmaw Gates', '3');
INSERT INTO `pvpareas` VALUES ('1039', 'The Lost Fleet', '3');
INSERT INTO `pvpareas` VALUES ('1056', 'Darrow Hill', '3');
INSERT INTO `pvpareas` VALUES ('1057', 'Thoradin\'s Wall', '3');
INSERT INTO `pvpareas` VALUES ('1076', 'Webwinder Path', '3');
INSERT INTO `pvpareas` VALUES ('1097', 'The Hushed Bank', '3');
INSERT INTO `pvpareas` VALUES ('1098', 'Manor Mistmantle', '3');
INSERT INTO `pvpareas` VALUES ('1099', 'Camp Mojache', '3');
INSERT INTO `pvpareas` VALUES ('1100', 'Grimtotem Compound', '3');
INSERT INTO `pvpareas` VALUES ('1101', 'The Writhing Deep', '3');
INSERT INTO `pvpareas` VALUES ('1102', 'Wildwind Lake', '3');
INSERT INTO `pvpareas` VALUES ('1103', 'Gordunni Outpost', '3');
INSERT INTO `pvpareas` VALUES ('1104', 'Mok\'Gordun', '3');
INSERT INTO `pvpareas` VALUES ('1105', 'Feral Scar Vale', '3');
INSERT INTO `pvpareas` VALUES ('1106', 'Frayfeather Highlands', '3');
INSERT INTO `pvpareas` VALUES ('1107', 'Idlewind Lake', '3');
INSERT INTO `pvpareas` VALUES ('1108', 'The Forgotten Coast', '3');
INSERT INTO `pvpareas` VALUES ('1109', 'East Pillar', '3');
INSERT INTO `pvpareas` VALUES ('1110', 'West Pillar', '3');
INSERT INTO `pvpareas` VALUES ('1111', 'Dream Bough', '3');
INSERT INTO `pvpareas` VALUES ('1112', 'Jademir Lake', '3');
INSERT INTO `pvpareas` VALUES ('1113', 'Oneiros', '3');
INSERT INTO `pvpareas` VALUES ('1114', 'Ruins of Ravenwind', '3');
INSERT INTO `pvpareas` VALUES ('1115', 'Rage Scar Hold', '3');
INSERT INTO `pvpareas` VALUES ('1116', 'Feathermoon Stronghold', '3');
INSERT INTO `pvpareas` VALUES ('1117', 'Ruins of Solarsal', '3');
INSERT INTO `pvpareas` VALUES ('1118', 'Lower Wilds', '3');
INSERT INTO `pvpareas` VALUES ('1119', 'The Twin Colossals', '3');
INSERT INTO `pvpareas` VALUES ('1120', 'Sardor Isle', '3');
INSERT INTO `pvpareas` VALUES ('1121', 'Isle of Dread', '3');
INSERT INTO `pvpareas` VALUES ('1136', 'High Wilderness', '3');
INSERT INTO `pvpareas` VALUES ('1137', 'Lower Wilds', '3');
INSERT INTO `pvpareas` VALUES ('1156', 'Southern Barrens', '2');
INSERT INTO `pvpareas` VALUES ('1157', 'Southern Gold Road', '2');
INSERT INTO `pvpareas` VALUES ('1176', 'Zul\'Farrak', '3');
INSERT INTO `pvpareas` VALUES ('1196', 'Alcaz Island', '3');
INSERT INTO `pvpareas` VALUES ('1216', 'Timbermaw Hold', '3');
INSERT INTO `pvpareas` VALUES ('1217', 'Vanndir Encampment', '3');
INSERT INTO `pvpareas` VALUES ('1218', 'TESTAzshara', '3');
INSERT INTO `pvpareas` VALUES ('1219', 'Legash Encampment', '3');
INSERT INTO `pvpareas` VALUES ('1220', 'Thalassian Base Camp', '3');
INSERT INTO `pvpareas` VALUES ('1221', 'Ruins of Eldarath', '3');
INSERT INTO `pvpareas` VALUES ('1222', 'Hetaera\'s Clutch', '3');
INSERT INTO `pvpareas` VALUES ('1223', 'Temple of Zin-Malor', '3');
INSERT INTO `pvpareas` VALUES ('1224', 'Bear\'s Head', '3');
INSERT INTO `pvpareas` VALUES ('1225', 'Ursolan', '3');
INSERT INTO `pvpareas` VALUES ('1226', 'Temple of Arkkoran', '3');
INSERT INTO `pvpareas` VALUES ('1227', 'Bay of Storms', '3');
INSERT INTO `pvpareas` VALUES ('1228', 'The Shattered Strand', '3');
INSERT INTO `pvpareas` VALUES ('1229', 'Tower of Eldara', '3');
INSERT INTO `pvpareas` VALUES ('1230', 'Jagged Reef', '3');
INSERT INTO `pvpareas` VALUES ('1231', 'Southridge Beach', '3');
INSERT INTO `pvpareas` VALUES ('1232', 'Ravencrest Monument', '3');
INSERT INTO `pvpareas` VALUES ('1233', 'Forlorn Ridge', '3');
INSERT INTO `pvpareas` VALUES ('1234', 'Lake Mennar', '3');
INSERT INTO `pvpareas` VALUES ('1235', 'Shadowsong Shrine', '3');
INSERT INTO `pvpareas` VALUES ('1236', 'Haldarr Encampment', '3');
INSERT INTO `pvpareas` VALUES ('1237', 'Valormok', '3');
INSERT INTO `pvpareas` VALUES ('1256', 'The Ruined Reaches', '3');
INSERT INTO `pvpareas` VALUES ('1276', 'The Talondeep Path', '3');
INSERT INTO `pvpareas` VALUES ('1277', 'The Talondeep Path', '3');
INSERT INTO `pvpareas` VALUES ('1296', 'Rocktusk Farm', '2');
INSERT INTO `pvpareas` VALUES ('1297', 'Jaggedswine Farm', '2');
INSERT INTO `pvpareas` VALUES ('1316', 'Razorfen Downs', '3');
INSERT INTO `pvpareas` VALUES ('1336', 'Lost Rigger Cove', '3');
INSERT INTO `pvpareas` VALUES ('1337', 'Uldaman', '3');
INSERT INTO `pvpareas` VALUES ('1338', 'Lordamere Lake', '3');
INSERT INTO `pvpareas` VALUES ('1339', 'Lordamere Lake', '3');
INSERT INTO `pvpareas` VALUES ('1357', 'Gallows\' Corner', '3');
INSERT INTO `pvpareas` VALUES ('1377', 'Silithus', '3');
INSERT INTO `pvpareas` VALUES ('1397', 'Emerald Forest', '3');
INSERT INTO `pvpareas` VALUES ('1417', 'Sunken Temple', '3');
INSERT INTO `pvpareas` VALUES ('1437', 'Dreadmaul Hold', '3');
INSERT INTO `pvpareas` VALUES ('1438', 'Nethergarde Keep', '3');
INSERT INTO `pvpareas` VALUES ('1439', 'Dreadmaul Post', '3');
INSERT INTO `pvpareas` VALUES ('1440', 'Serpent\'s Coil', '3');
INSERT INTO `pvpareas` VALUES ('1441', 'Altar of Storms', '3');
INSERT INTO `pvpareas` VALUES ('1442', 'Firewatch Ridge', '3');
INSERT INTO `pvpareas` VALUES ('1443', 'The Slag Pit', '3');
INSERT INTO `pvpareas` VALUES ('1444', 'The Sea of Cinders', '3');
INSERT INTO `pvpareas` VALUES ('1445', 'Blackrock Mountain', '3');
INSERT INTO `pvpareas` VALUES ('1446', 'Thorium Point', '3');
INSERT INTO `pvpareas` VALUES ('1457', 'Garrison Armory', '3');
INSERT INTO `pvpareas` VALUES ('1477', 'The Temple of Atal\'Hakkar', '3');
INSERT INTO `pvpareas` VALUES ('1497', 'Undercity', '2');
INSERT INTO `pvpareas` VALUES ('1517', 'Uldaman', '3');
INSERT INTO `pvpareas` VALUES ('1518', 'Not Used Deadmines', '1');
INSERT INTO `pvpareas` VALUES ('1519', 'Stormwind City', '1');
INSERT INTO `pvpareas` VALUES ('1537', 'Ironforge', '1');
INSERT INTO `pvpareas` VALUES ('1557', 'Splithoof Hold', '3');
INSERT INTO `pvpareas` VALUES ('1577', 'The Cape of Stranglethorn', '3');
INSERT INTO `pvpareas` VALUES ('1578', 'Southern Savage Coast', '3');
INSERT INTO `pvpareas` VALUES ('1579', ' The Deadmines 002', '1');
INSERT INTO `pvpareas` VALUES ('1580', ' Ironclad Cove 003', '0');
INSERT INTO `pvpareas` VALUES ('1581', 'The Deadmines', '1');
INSERT INTO `pvpareas` VALUES ('1582', 'Ironclad Cove', '3');
INSERT INTO `pvpareas` VALUES ('1583', 'Blackrock Spire', '3');
INSERT INTO `pvpareas` VALUES ('1584', 'Blackrock Depths', '3');
INSERT INTO `pvpareas` VALUES ('1597', 'Raptor Grounds', '2');
INSERT INTO `pvpareas` VALUES ('1598', 'Grol\'dom Farm', '2');
INSERT INTO `pvpareas` VALUES ('1599', 'Mor\'shan Base Camp', '2');
INSERT INTO `pvpareas` VALUES ('1600', 'Honor\'s Stand', '2');
INSERT INTO `pvpareas` VALUES ('1601', 'Blackthorn Ridge', '2');
INSERT INTO `pvpareas` VALUES ('1602', 'Bramblescar', '2');
INSERT INTO `pvpareas` VALUES ('1603', 'Agama\'gor', '2');
INSERT INTO `pvpareas` VALUES ('1617', 'Valley of Heroes', '1');
INSERT INTO `pvpareas` VALUES ('1637', 'Orgrimmar', '2');
INSERT INTO `pvpareas` VALUES ('1638', 'Thunder Bluff', '2');
INSERT INTO `pvpareas` VALUES ('1639', 'Elder Rise', '2');
INSERT INTO `pvpareas` VALUES ('1640', 'Spirit Rise', '2');
INSERT INTO `pvpareas` VALUES ('1641', 'Hunter Rise', '2');
INSERT INTO `pvpareas` VALUES ('1657', 'Darnassus', '1');
INSERT INTO `pvpareas` VALUES ('1658', 'Cenarion Enclave', '1');
INSERT INTO `pvpareas` VALUES ('1659', 'Craftsmen\'s Terrace', '1');
INSERT INTO `pvpareas` VALUES ('1660', 'Warrior\'s Terrace', '1');
INSERT INTO `pvpareas` VALUES ('1661', 'The Temple Gardens', '1');
INSERT INTO `pvpareas` VALUES ('1662', 'Tradesmen\'s Terrace', '1');
INSERT INTO `pvpareas` VALUES ('1677', 'Gavin\'s Naze', '3');
INSERT INTO `pvpareas` VALUES ('1678', 'Sofera\'s Naze', '3');
INSERT INTO `pvpareas` VALUES ('1679', 'Corrahn\'s Dagger', '3');
INSERT INTO `pvpareas` VALUES ('1680', 'The Headland', '3');
INSERT INTO `pvpareas` VALUES ('1681', 'Misty Shore', '3');
INSERT INTO `pvpareas` VALUES ('1682', 'Dandred\'s Fold', '3');
INSERT INTO `pvpareas` VALUES ('1683', 'Growless Cave', '3');
INSERT INTO `pvpareas` VALUES ('1684', 'Chillwind Point', '3');
INSERT INTO `pvpareas` VALUES ('1697', 'Raptor Grounds', '2');
INSERT INTO `pvpareas` VALUES ('1698', 'Bramblescar', '2');
INSERT INTO `pvpareas` VALUES ('1699', 'Thorn Hill', '2');
INSERT INTO `pvpareas` VALUES ('1700', 'Agama\'gor', '2');
INSERT INTO `pvpareas` VALUES ('1701', 'Blackthorn Ridge', '2');
INSERT INTO `pvpareas` VALUES ('1702', 'Honor\'s Stand', '2');
INSERT INTO `pvpareas` VALUES ('1703', 'The Mor\'shan Rampart', '2');
INSERT INTO `pvpareas` VALUES ('1704', 'Grol\'dom Farm', '2');
INSERT INTO `pvpareas` VALUES ('1717', 'Razorfen Kraul', '3');
INSERT INTO `pvpareas` VALUES ('1718', 'The Great Lift', '3');
INSERT INTO `pvpareas` VALUES ('1737', 'Mistvale Valley', '3');
INSERT INTO `pvpareas` VALUES ('1738', 'Nek\'mani Wellspring', '3');
INSERT INTO `pvpareas` VALUES ('1739', 'Bloodsail Compound', '3');
INSERT INTO `pvpareas` VALUES ('1740', 'Venture Co. Base Camp', '3');
INSERT INTO `pvpareas` VALUES ('1741', 'Gurubashi Arena', '3');
INSERT INTO `pvpareas` VALUES ('1742', 'Spirit Den', '3');
INSERT INTO `pvpareas` VALUES ('1757', 'The Crimson Veil', '3');
INSERT INTO `pvpareas` VALUES ('1758', 'The Riptide', '3');
INSERT INTO `pvpareas` VALUES ('1759', 'The Damsel\'s Luck', '3');
INSERT INTO `pvpareas` VALUES ('1760', 'Venture Co. Operations Center', '3');
INSERT INTO `pvpareas` VALUES ('1761', 'Deadwood Village', '3');
INSERT INTO `pvpareas` VALUES ('1762', 'Felpaw Village', '3');
INSERT INTO `pvpareas` VALUES ('1763', 'Jaedenar', '3');
INSERT INTO `pvpareas` VALUES ('1764', 'Bloodvenom River', '3');
INSERT INTO `pvpareas` VALUES ('1765', 'Bloodvenom Falls', '3');
INSERT INTO `pvpareas` VALUES ('1766', 'Shatter Scar Vale', '3');
INSERT INTO `pvpareas` VALUES ('1767', 'Irontree Woods', '3');
INSERT INTO `pvpareas` VALUES ('1768', 'Irontree Cavern', '3');
INSERT INTO `pvpareas` VALUES ('1769', 'Timbermaw Hold', '3');
INSERT INTO `pvpareas` VALUES ('1770', 'Shadow Hold', '3');
INSERT INTO `pvpareas` VALUES ('1771', 'Shrine of the Deceiver', '3');
INSERT INTO `pvpareas` VALUES ('1777', 'Itharius\'s Cave', '3');
INSERT INTO `pvpareas` VALUES ('1778', 'Sorrowmurk', '3');
INSERT INTO `pvpareas` VALUES ('1779', 'Draenil\'dur Village', '3');
INSERT INTO `pvpareas` VALUES ('1780', 'Splinterspear Junction', '3');
INSERT INTO `pvpareas` VALUES ('1797', 'Stagalbog', '3');
INSERT INTO `pvpareas` VALUES ('1798', 'The Shifting Mire', '3');
INSERT INTO `pvpareas` VALUES ('1817', 'Stagalbog Cave', '3');
INSERT INTO `pvpareas` VALUES ('1837', 'Witherbark Caverns', '3');
INSERT INTO `pvpareas` VALUES ('1857', 'Thoradin\'s Wall', '3');
INSERT INTO `pvpareas` VALUES ('1858', 'Boulder\'gor', '3');
INSERT INTO `pvpareas` VALUES ('1877', 'Valley of Fangs', '3');
INSERT INTO `pvpareas` VALUES ('1878', 'The Dustbowl', '3');
INSERT INTO `pvpareas` VALUES ('1879', 'Mirage Flats', '3');
INSERT INTO `pvpareas` VALUES ('1880', 'Featherbeard\'s Hovel', '3');
INSERT INTO `pvpareas` VALUES ('1881', 'Shindigger\'s Camp', '3');
INSERT INTO `pvpareas` VALUES ('1882', 'Plaguemist Ravine', '3');
INSERT INTO `pvpareas` VALUES ('1883', 'Valorwind Lake', '3');
INSERT INTO `pvpareas` VALUES ('1884', 'Agol\'watha', '3');
INSERT INTO `pvpareas` VALUES ('1885', 'Hiri\'watha', '3');
INSERT INTO `pvpareas` VALUES ('1886', 'The Creeping Ruin', '3');
INSERT INTO `pvpareas` VALUES ('1887', 'Bogen\'s Ledge', '3');
INSERT INTO `pvpareas` VALUES ('1897', 'The Maker\'s Terrace', '3');
INSERT INTO `pvpareas` VALUES ('1898', 'Dustwind Gulch', '3');
INSERT INTO `pvpareas` VALUES ('1917', 'Shaol\'watha', '3');
INSERT INTO `pvpareas` VALUES ('1937', 'Noonshade Ruins', '3');
INSERT INTO `pvpareas` VALUES ('1938', 'Broken Pillar', '3');
INSERT INTO `pvpareas` VALUES ('1939', 'Abyssal Sands', '3');
INSERT INTO `pvpareas` VALUES ('1940', 'Southbreak Shore', '3');
INSERT INTO `pvpareas` VALUES ('1941', 'Caverns of Time', '3');
INSERT INTO `pvpareas` VALUES ('1942', 'The Marshlands', '3');
INSERT INTO `pvpareas` VALUES ('1943', 'Ironstone Plateau', '2');
INSERT INTO `pvpareas` VALUES ('1957', 'Blackchar Cave', '3');
INSERT INTO `pvpareas` VALUES ('1958', 'Tanner Camp', '3');
INSERT INTO `pvpareas` VALUES ('1959', 'Dustfire Valley', '3');
INSERT INTO `pvpareas` VALUES ('1977', 'Zul\'Gurub', '3');
INSERT INTO `pvpareas` VALUES ('1978', 'Misty Reed Post', '3');
INSERT INTO `pvpareas` VALUES ('1997', 'Bloodvenom Post', '3');
INSERT INTO `pvpareas` VALUES ('1998', 'Talonbranch Glade', '3');
INSERT INTO `pvpareas` VALUES ('2017', 'Stratholme', '3');
INSERT INTO `pvpareas` VALUES ('2037', 'Shadowfang Keep 003', '2');
INSERT INTO `pvpareas` VALUES ('2057', 'Scholomance', '3');
INSERT INTO `pvpareas` VALUES ('2077', 'Twilight Vale', '1');
INSERT INTO `pvpareas` VALUES ('2078', 'Twilight Shore', '1');
INSERT INTO `pvpareas` VALUES ('2079', 'Alcaz Island', '1');
INSERT INTO `pvpareas` VALUES ('2097', 'Darkcloud Pinnacle', '3');
INSERT INTO `pvpareas` VALUES ('2098', 'Dawning Wood Catacombs', '3');
INSERT INTO `pvpareas` VALUES ('2099', 'Stonewatch Keep', '3');
INSERT INTO `pvpareas` VALUES ('2100', 'Maraudon', '3');
INSERT INTO `pvpareas` VALUES ('2101', 'Stoutlager Inn', '1');
INSERT INTO `pvpareas` VALUES ('2102', 'Thunderbrew Distillery', '1');
INSERT INTO `pvpareas` VALUES ('2103', 'Menethil Keep', '3');
INSERT INTO `pvpareas` VALUES ('2104', 'Deepwater Tavern', '3');
INSERT INTO `pvpareas` VALUES ('2117', 'Shadow Grave', '2');
INSERT INTO `pvpareas` VALUES ('2118', 'Brill Town Hall', '2');
INSERT INTO `pvpareas` VALUES ('2119', 'Gallows\' End Tavern', '2');
INSERT INTO `pvpareas` VALUES ('2137', 'The Pools of Vision', '2');
INSERT INTO `pvpareas` VALUES ('2138', 'Dreadmist Den', '2');
INSERT INTO `pvpareas` VALUES ('2157', 'Bael\'dun Keep', '2');
INSERT INTO `pvpareas` VALUES ('2158', 'Emberstrife\'s Den', '3');
INSERT INTO `pvpareas` VALUES ('2159', 'Onyxia\'s Lair', '3');
INSERT INTO `pvpareas` VALUES ('2160', 'Windshear Mine', '3');
INSERT INTO `pvpareas` VALUES ('2161', 'Roland\'s Doom', '3');
INSERT INTO `pvpareas` VALUES ('2177', 'Battle Ring', '4');
INSERT INTO `pvpareas` VALUES ('2197', 'The Pools of Vision', '2');
INSERT INTO `pvpareas` VALUES ('2198', 'Shadowbreak Ravine', '3');
INSERT INTO `pvpareas` VALUES ('2217', 'Broken Spear Village', '3');
INSERT INTO `pvpareas` VALUES ('2237', 'Whitereach Post', '3');
INSERT INTO `pvpareas` VALUES ('2238', 'Gornia', '3');
INSERT INTO `pvpareas` VALUES ('2239', 'Zane\'s Eye Crater', '3');
INSERT INTO `pvpareas` VALUES ('2240', 'Mirage Raceway', '3');
INSERT INTO `pvpareas` VALUES ('2241', 'Frostsaber Rock', '3');
INSERT INTO `pvpareas` VALUES ('2242', 'The Hidden Grove', '3');
INSERT INTO `pvpareas` VALUES ('2243', 'Timbermaw Post', '3');
INSERT INTO `pvpareas` VALUES ('2244', 'Winterfall Village', '3');
INSERT INTO `pvpareas` VALUES ('2245', 'Mazthoril', '3');
INSERT INTO `pvpareas` VALUES ('2246', 'Frostfire Hot Springs', '3');
INSERT INTO `pvpareas` VALUES ('2247', 'Ice Thistle Hills', '3');
INSERT INTO `pvpareas` VALUES ('2248', 'Dun Mandarr', '3');
INSERT INTO `pvpareas` VALUES ('2249', 'Frostwhisper Gorge', '3');
INSERT INTO `pvpareas` VALUES ('2250', 'Owl Wing Thicket', '3');
INSERT INTO `pvpareas` VALUES ('2251', 'Lake Kel\'Theril', '3');
INSERT INTO `pvpareas` VALUES ('2252', 'The Ruins of Kel\'Theril', '3');
INSERT INTO `pvpareas` VALUES ('2253', 'Starfall Village', '3');
INSERT INTO `pvpareas` VALUES ('2254', 'Ban\'Thallow Barrow Den', '3');
INSERT INTO `pvpareas` VALUES ('2255', 'Everlook', '3');
INSERT INTO `pvpareas` VALUES ('2256', 'Darkwhisper Gorge', '3');
INSERT INTO `pvpareas` VALUES ('2257', 'Deeprun Tram', '1');
INSERT INTO `pvpareas` VALUES ('2258', 'The Fungal Vale', '0');
INSERT INTO `pvpareas` VALUES ('2259', 'The Marris Stead', '3');
INSERT INTO `pvpareas` VALUES ('2260', 'The Marris Stead', '3');
INSERT INTO `pvpareas` VALUES ('2261', 'The Undercroft', '3');
INSERT INTO `pvpareas` VALUES ('2262', 'Darrowshire', '3');
INSERT INTO `pvpareas` VALUES ('2263', 'Crown Guard Tower', '3');
INSERT INTO `pvpareas` VALUES ('2264', 'Corin\'s Crossing', '3');
INSERT INTO `pvpareas` VALUES ('2265', 'Scarlet Base Camp', '3');
INSERT INTO `pvpareas` VALUES ('2266', 'Tyr\'s Hand', '3');
INSERT INTO `pvpareas` VALUES ('2267', 'The Scarlet Basilica', '3');
INSERT INTO `pvpareas` VALUES ('2268', 'Light\'s Hope Chapel', '3');
INSERT INTO `pvpareas` VALUES ('2269', 'Browman Mill', '3');
INSERT INTO `pvpareas` VALUES ('2270', 'The Noxious Glade', '3');
INSERT INTO `pvpareas` VALUES ('2271', 'Eastwall Tower', '3');
INSERT INTO `pvpareas` VALUES ('2272', 'Northdale', '3');
INSERT INTO `pvpareas` VALUES ('2273', 'Zul\'Mashar', '3');
INSERT INTO `pvpareas` VALUES ('2274', 'Mazra\'Alor', '3');
INSERT INTO `pvpareas` VALUES ('2275', 'Northpass Tower', '3');
INSERT INTO `pvpareas` VALUES ('2276', 'Quel\'Lithien Lodge', '3');
INSERT INTO `pvpareas` VALUES ('2277', 'Plaguewood', '3');
INSERT INTO `pvpareas` VALUES ('2278', 'Scourgehold', '3');
INSERT INTO `pvpareas` VALUES ('2279', 'Stratholme', '3');
INSERT INTO `pvpareas` VALUES ('2280', ' Stratholme', '3');
INSERT INTO `pvpareas` VALUES ('2297', 'Darrowmere Lake', '3');
INSERT INTO `pvpareas` VALUES ('2298', 'Caer Darrow', '3');
INSERT INTO `pvpareas` VALUES ('2299', 'Darrowmere Lake', '3');
INSERT INTO `pvpareas` VALUES ('2300', 'Caverns of Time', '3');
INSERT INTO `pvpareas` VALUES ('2301', 'Thistlefur Village', '3');
INSERT INTO `pvpareas` VALUES ('2302', 'The Quagmire', '3');
INSERT INTO `pvpareas` VALUES ('2303', 'Windbreak Canyon', '3');
INSERT INTO `pvpareas` VALUES ('2317', 'South Seas', '3');
INSERT INTO `pvpareas` VALUES ('2318', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2319', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2320', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2321', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2322', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('2323', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('2324', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('2325', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('2326', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('2337', 'Razor Hill Barracks', '2');
INSERT INTO `pvpareas` VALUES ('2338', 'South Seas', '3');
INSERT INTO `pvpareas` VALUES ('2339', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2357', 'Bloodtooth Camp', '3');
INSERT INTO `pvpareas` VALUES ('2358', 'Forest Song', '3');
INSERT INTO `pvpareas` VALUES ('2359', 'Greenpaw Village', '3');
INSERT INTO `pvpareas` VALUES ('2360', 'Silverwing Outpost', '3');
INSERT INTO `pvpareas` VALUES ('2361', 'Nighthaven', '3');
INSERT INTO `pvpareas` VALUES ('2362', 'Shrine of Remulos', '3');
INSERT INTO `pvpareas` VALUES ('2363', 'Stormrage Barrow Dens', '3');
INSERT INTO `pvpareas` VALUES ('2364', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2365', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2366', 'The Black Morass', '3');
INSERT INTO `pvpareas` VALUES ('2367', 'Old Hillsbrad Foothills', '3');
INSERT INTO `pvpareas` VALUES ('2368', 'Tarren Mill', '3');
INSERT INTO `pvpareas` VALUES ('2369', 'Southshore', '3');
INSERT INTO `pvpareas` VALUES ('2370', 'Durnholde Keep', '3');
INSERT INTO `pvpareas` VALUES ('2371', 'Dun Garok', '3');
INSERT INTO `pvpareas` VALUES ('2372', 'Hillsbrad Fields', '3');
INSERT INTO `pvpareas` VALUES ('2373', 'Eastern Strand', '3');
INSERT INTO `pvpareas` VALUES ('2374', 'Nethander Stead', '3');
INSERT INTO `pvpareas` VALUES ('2375', 'Darrow Hill', '3');
INSERT INTO `pvpareas` VALUES ('2376', 'Southpoint Tower', '3');
INSERT INTO `pvpareas` VALUES ('2377', 'Thoradin\'s Wall', '3');
INSERT INTO `pvpareas` VALUES ('2378', 'Western Strand', '3');
INSERT INTO `pvpareas` VALUES ('2379', 'Azurelode Mine', '3');
INSERT INTO `pvpareas` VALUES ('2397', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2398', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2399', 'The Great Sea', '3');
INSERT INTO `pvpareas` VALUES ('2400', 'The Forbidding Sea', '3');
INSERT INTO `pvpareas` VALUES ('2401', 'The Forbidding Sea', '3');
INSERT INTO `pvpareas` VALUES ('2402', 'The Forbidding Sea', '3');
INSERT INTO `pvpareas` VALUES ('2403', 'The Forbidding Sea', '3');
INSERT INTO `pvpareas` VALUES ('2404', 'Tethris Aran', '3');
INSERT INTO `pvpareas` VALUES ('2405', 'Ethel Rethor', '3');
INSERT INTO `pvpareas` VALUES ('2406', 'Ranazjar Isle', '3');
INSERT INTO `pvpareas` VALUES ('2407', 'Kormek\'s Hut', '3');
INSERT INTO `pvpareas` VALUES ('2408', 'Shadowprey Village', '3');
INSERT INTO `pvpareas` VALUES ('2417', 'Blackrock Pass', '3');
INSERT INTO `pvpareas` VALUES ('2418', 'Morgan\'s Vigil', '3');
INSERT INTO `pvpareas` VALUES ('2419', 'Slither Rock', '3');
INSERT INTO `pvpareas` VALUES ('2420', 'Terror Wing Path', '3');
INSERT INTO `pvpareas` VALUES ('2421', 'Draco\'dar', '3');
INSERT INTO `pvpareas` VALUES ('2437', 'Ragefire Chasm', '2');
INSERT INTO `pvpareas` VALUES ('2457', 'Nightsong Woods', '3');
INSERT INTO `pvpareas` VALUES ('2477', 'The Veiled Sea', '3');
INSERT INTO `pvpareas` VALUES ('2478', 'Morlos\'Aran', '3');
INSERT INTO `pvpareas` VALUES ('2479', 'Emerald Sanctuary', '3');
INSERT INTO `pvpareas` VALUES ('2480', 'Jadefire Glen', '3');
INSERT INTO `pvpareas` VALUES ('2481', 'Ruins of Constellas', '3');
INSERT INTO `pvpareas` VALUES ('2497', 'Bitter Reaches', '3');
INSERT INTO `pvpareas` VALUES ('2517', 'Rise of the Defiler', '3');
INSERT INTO `pvpareas` VALUES ('2518', 'Lariss Pavilion', '3');
INSERT INTO `pvpareas` VALUES ('2519', 'Woodpaw Hills', '3');
INSERT INTO `pvpareas` VALUES ('2520', 'Woodpaw Den', '3');
INSERT INTO `pvpareas` VALUES ('2521', 'Verdantis River', '3');
INSERT INTO `pvpareas` VALUES ('2522', 'Ruins of Isildien', '3');
INSERT INTO `pvpareas` VALUES ('2537', 'Grimtotem Post', '3');
INSERT INTO `pvpareas` VALUES ('2538', 'Camp Aparaje', '3');
INSERT INTO `pvpareas` VALUES ('2539', 'Malaka\'jin', '3');
INSERT INTO `pvpareas` VALUES ('2540', 'Boulderslide Ravine', '3');
INSERT INTO `pvpareas` VALUES ('2541', 'Sishir Canyon', '3');
INSERT INTO `pvpareas` VALUES ('2557', 'Dire Maul', '3');
INSERT INTO `pvpareas` VALUES ('2558', 'Deadwind Ravine', '3');
INSERT INTO `pvpareas` VALUES ('2559', 'Diamondhead River', '3');
INSERT INTO `pvpareas` VALUES ('2560', 'Ariden\'s Camp', '3');
INSERT INTO `pvpareas` VALUES ('2561', 'The Vice', '3');
INSERT INTO `pvpareas` VALUES ('2562', 'Karazhan', '3');
INSERT INTO `pvpareas` VALUES ('2563', 'Morgan\'s Plot', '3');
INSERT INTO `pvpareas` VALUES ('2577', 'Dire Maul', '3');
INSERT INTO `pvpareas` VALUES ('2597', 'Alterac Valley', '3');
INSERT INTO `pvpareas` VALUES ('2617', 'Scrabblescrew\'s Camp', '3');
INSERT INTO `pvpareas` VALUES ('2618', 'Jadefire Run', '3');
INSERT INTO `pvpareas` VALUES ('2619', 'Thondroril River', '3');
INSERT INTO `pvpareas` VALUES ('2620', 'Thondroril River', '3');
INSERT INTO `pvpareas` VALUES ('2621', 'Lake Mereldar', '3');
INSERT INTO `pvpareas` VALUES ('2622', 'Pestilent Scar', '3');
INSERT INTO `pvpareas` VALUES ('2623', 'The Infectis Scar', '3');
INSERT INTO `pvpareas` VALUES ('2624', 'Blackwood Lake', '3');
INSERT INTO `pvpareas` VALUES ('2625', 'Eastwall Gate', '3');
INSERT INTO `pvpareas` VALUES ('2626', 'Terrorweb Tunnel', '3');
INSERT INTO `pvpareas` VALUES ('2627', 'Terrordale', '3');
INSERT INTO `pvpareas` VALUES ('2637', 'Kargathia Keep', '3');
INSERT INTO `pvpareas` VALUES ('2657', 'Valley of Bones', '3');
INSERT INTO `pvpareas` VALUES ('2677', 'Blackwing Lair', '3');
INSERT INTO `pvpareas` VALUES ('2697', 'Deadman\'s Crossing', '3');
INSERT INTO `pvpareas` VALUES ('2717', 'Molten Core', '3');
INSERT INTO `pvpareas` VALUES ('2737', 'The Scarab Wall', '3');
INSERT INTO `pvpareas` VALUES ('2738', 'Southwind Village', '3');
INSERT INTO `pvpareas` VALUES ('2739', 'Twilight Base Camp', '3');
INSERT INTO `pvpareas` VALUES ('2740', 'The Crystal Vale', '3');
INSERT INTO `pvpareas` VALUES ('2741', 'The Scarab Dais', '3');
INSERT INTO `pvpareas` VALUES ('2742', 'Hive\'Ashi', '3');
INSERT INTO `pvpareas` VALUES ('2743', 'Hive\'Zora', '3');
INSERT INTO `pvpareas` VALUES ('2744', 'Hive\'Regal', '3');
INSERT INTO `pvpareas` VALUES ('2757', 'Shrine of the Fallen Warrior', '2');
INSERT INTO `pvpareas` VALUES ('2777', ' Alterac Valley', '3');
INSERT INTO `pvpareas` VALUES ('2797', 'Blackfathom Deeps', '3');
INSERT INTO `pvpareas` VALUES ('2817', '***On Map Dungeon***', '0');
INSERT INTO `pvpareas` VALUES ('2837', 'The Master\'s Cellar', '3');
INSERT INTO `pvpareas` VALUES ('2838', 'Stonewrought Pass', '3');
INSERT INTO `pvpareas` VALUES ('2839', 'Alterac Valley', '3');
INSERT INTO `pvpareas` VALUES ('2857', 'The Rumble Cage', '3');
INSERT INTO `pvpareas` VALUES ('2897', 'Zoram\'gar Outpost', '3');
INSERT INTO `pvpareas` VALUES ('2917', 'Hall of Legends', '2');
INSERT INTO `pvpareas` VALUES ('2918', 'Champions\' Hall', '1');
INSERT INTO `pvpareas` VALUES ('2937', 'Grosh\'gok Compound', '3');
INSERT INTO `pvpareas` VALUES ('2938', 'Sleeping Gorge', '3');
INSERT INTO `pvpareas` VALUES ('2957', 'Irondeep Mine', '3');
INSERT INTO `pvpareas` VALUES ('2958', 'Stonehearth Outpost', '3');
INSERT INTO `pvpareas` VALUES ('2959', 'Dun Baldar', '3');
INSERT INTO `pvpareas` VALUES ('2960', 'Icewing Pass', '3');
INSERT INTO `pvpareas` VALUES ('2961', 'Frostwolf Village', '3');
INSERT INTO `pvpareas` VALUES ('2962', 'Tower Point', '3');
INSERT INTO `pvpareas` VALUES ('2963', 'Coldtooth Mine', '3');
INSERT INTO `pvpareas` VALUES ('2964', 'Winterax Hold', '3');
INSERT INTO `pvpareas` VALUES ('2977', 'Iceblood Garrison', '3');
INSERT INTO `pvpareas` VALUES ('2978', 'Frostwolf Keep', '3');
INSERT INTO `pvpareas` VALUES ('2979', 'Tor\'kren Farm', '3');
INSERT INTO `pvpareas` VALUES ('3017', 'Frost Dagger Pass', '3');
INSERT INTO `pvpareas` VALUES ('3037', 'Ironstone Camp', '3');
INSERT INTO `pvpareas` VALUES ('3038', 'Weazel\'s Crater', '3');
INSERT INTO `pvpareas` VALUES ('3039', 'Tahonda Ruins', '3');
INSERT INTO `pvpareas` VALUES ('3057', 'Field of Strife', '3');
INSERT INTO `pvpareas` VALUES ('3058', 'Icewing Cavern', '3');
INSERT INTO `pvpareas` VALUES ('3077', 'Valor\'s Rest', '3');
INSERT INTO `pvpareas` VALUES ('3097', 'The Swarming Pillar', '3');
INSERT INTO `pvpareas` VALUES ('3098', 'Twilight Post', '3');
INSERT INTO `pvpareas` VALUES ('3099', 'Twilight Outpost', '3');
INSERT INTO `pvpareas` VALUES ('3100', 'Ravaged Twilight Camp', '3');
INSERT INTO `pvpareas` VALUES ('3117', 'Shalzaru\'s Lair', '3');
INSERT INTO `pvpareas` VALUES ('3137', 'Talrendis Point', '3');
INSERT INTO `pvpareas` VALUES ('3138', 'Rethress Sanctum', '3');
INSERT INTO `pvpareas` VALUES ('3139', 'Moon Horror Den', '3');
INSERT INTO `pvpareas` VALUES ('3140', 'Scalebeard\'s Cave', '3');
INSERT INTO `pvpareas` VALUES ('3157', 'Boulderslide Cavern', '3');
INSERT INTO `pvpareas` VALUES ('3177', 'Warsong Labor Camp', '3');
INSERT INTO `pvpareas` VALUES ('3197', 'Chillwind Camp', '3');
INSERT INTO `pvpareas` VALUES ('3217', 'The Maul', '4');
INSERT INTO `pvpareas` VALUES ('3237', 'The Maul', '4');
INSERT INTO `pvpareas` VALUES ('3257', 'Bones of Grakkarond', '3');
INSERT INTO `pvpareas` VALUES ('3277', 'Warsong Gulch', '3');
INSERT INTO `pvpareas` VALUES ('3297', 'Frostwolf Graveyard', '3');
INSERT INTO `pvpareas` VALUES ('3298', 'Frostwolf Pass', '3');
INSERT INTO `pvpareas` VALUES ('3299', 'Dun Baldar Pass', '3');
INSERT INTO `pvpareas` VALUES ('3300', 'Iceblood Graveyard', '3');
INSERT INTO `pvpareas` VALUES ('3301', 'Snowfall Graveyard', '3');
INSERT INTO `pvpareas` VALUES ('3302', 'Stonehearth Graveyard', '3');
INSERT INTO `pvpareas` VALUES ('3303', 'Stormpike Graveyard', '3');
INSERT INTO `pvpareas` VALUES ('3304', 'Icewing Bunker', '3');
INSERT INTO `pvpareas` VALUES ('3305', 'Stonehearth Bunker', '3');
INSERT INTO `pvpareas` VALUES ('3306', 'Wildpaw Ridge', '3');
INSERT INTO `pvpareas` VALUES ('3317', 'Revantusk Village', '3');
INSERT INTO `pvpareas` VALUES ('3318', 'Rock of Durotan', '3');
INSERT INTO `pvpareas` VALUES ('3319', 'Silverwing Grove', '3');
INSERT INTO `pvpareas` VALUES ('3320', 'Warsong Lumber Mill', '3');
INSERT INTO `pvpareas` VALUES ('3321', 'Silverwing Hold', '3');
INSERT INTO `pvpareas` VALUES ('3337', 'Wildpaw Cavern', '3');
INSERT INTO `pvpareas` VALUES ('3338', 'The Veiled Cleft', '3');
INSERT INTO `pvpareas` VALUES ('3357', 'Yojamba Isle', '3');
INSERT INTO `pvpareas` VALUES ('3358', 'Arathi Basin', '3');
INSERT INTO `pvpareas` VALUES ('3377', 'The Coil', '3');
INSERT INTO `pvpareas` VALUES ('3378', 'Altar of Hir\'eek', '3');
INSERT INTO `pvpareas` VALUES ('3379', 'Shadra\'zaar', '3');
INSERT INTO `pvpareas` VALUES ('3380', 'Hakkari Grounds', '3');
INSERT INTO `pvpareas` VALUES ('3381', 'Naze of Shirvallah', '3');
INSERT INTO `pvpareas` VALUES ('3382', 'Temple of Bethekk', '3');
INSERT INTO `pvpareas` VALUES ('3383', 'The Bloodfire Pit', '3');
INSERT INTO `pvpareas` VALUES ('3384', 'Altar of the Blood God', '3');
INSERT INTO `pvpareas` VALUES ('3397', 'Zanza\'s Rise', '3');
INSERT INTO `pvpareas` VALUES ('3398', 'Edge of Madness', '3');
INSERT INTO `pvpareas` VALUES ('3417', 'Trollbane Hall', '3');
INSERT INTO `pvpareas` VALUES ('3418', 'Defiler\'s Den', '3');
INSERT INTO `pvpareas` VALUES ('3419', 'Pagle\'s Pointe', '3');
INSERT INTO `pvpareas` VALUES ('3420', 'Farm', '3');
INSERT INTO `pvpareas` VALUES ('3421', 'Blacksmith', '3');
INSERT INTO `pvpareas` VALUES ('3422', 'Lumber Mill', '3');
INSERT INTO `pvpareas` VALUES ('3423', 'Gold Mine', '3');
INSERT INTO `pvpareas` VALUES ('3424', 'Stables', '3');
INSERT INTO `pvpareas` VALUES ('3425', 'Cenarion Hold', '0');
INSERT INTO `pvpareas` VALUES ('3426', 'Staghelm Point', '3');
INSERT INTO `pvpareas` VALUES ('3427', 'Bronzebeard Encampment', '3');
INSERT INTO `pvpareas` VALUES ('3446', 'Twilight\'s Run', '3');
INSERT INTO `pvpareas` VALUES ('3447', 'Ortell\'s Hideout', '3');
INSERT INTO `pvpareas` VALUES ('3522', 'Blade\'s Edge Mountains', '3');
INSERT INTO `pvpareas` VALUES ('3483', 'Hellfire Peninsula', '3');
INSERT INTO `pvpareas` VALUES ('3518', 'Nagrand', '3');
INSERT INTO `pvpareas` VALUES ('3523', 'Netherstorm', '3');
INSERT INTO `pvpareas` VALUES ('3520', 'Shadowmoon Valley', '3');
INSERT INTO `pvpareas` VALUES ('3519', 'Terokkar Forest', '3');
INSERT INTO `pvpareas` VALUES ('3521', 'Zangarmarsh', '3');
INSERT INTO `pvpareas` VALUES ('3703', 'Shattrath City', '0');

-- ----------------------------
-- Table structure for `questlog`
-- ----------------------------
DROP TABLE IF EXISTS `questlog`;
CREATE TABLE `questlog` (
  `index` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `player_guid` int(11) unsigned NOT NULL DEFAULT '0',
  `quest_id` int(10) unsigned NOT NULL DEFAULT '0',
  `slot` int(20) unsigned NOT NULL DEFAULT '0',
  `time_left` int(10) NOT NULL DEFAULT '0',
  `explored_area1` int(20) unsigned NOT NULL DEFAULT '0',
  `explored_area2` int(20) unsigned NOT NULL DEFAULT '0',
  `explored_area3` int(20) unsigned NOT NULL DEFAULT '0',
  `explored_area4` int(20) unsigned NOT NULL DEFAULT '0',
  `mob_kill1` int(20) NOT NULL DEFAULT '0',
  `mob_kill2` int(20) NOT NULL DEFAULT '0',
  `mob_kill3` int(20) NOT NULL DEFAULT '0',
  `mob_kill4` int(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  KEY `index` (`index`)
) ENGINE=MyISAM AUTO_INCREMENT=9623886 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of questlog
-- ----------------------------

-- ----------------------------
-- Table structure for `quests`
-- ----------------------------
DROP TABLE IF EXISTS `quests`;
CREATE TABLE `quests` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `ZoneId` int(11) unsigned NOT NULL DEFAULT '0',
  `QuestSort` int(11) unsigned NOT NULL DEFAULT '0',
  `QuestFlags` int(11) unsigned NOT NULL DEFAULT '0',
  `MinLevel` int(11) unsigned NOT NULL DEFAULT '0',
  `MaxLevel` int(11) unsigned NOT NULL DEFAULT '0',
  `Type` int(11) unsigned NOT NULL DEFAULT '0',
  `RequiredRaces` int(11) unsigned NOT NULL DEFAULT '0',
  `RequiredClass` int(11) unsigned NOT NULL DEFAULT '0',
  `RequiredTradeskill` int(11) unsigned NOT NULL DEFAULT '0',
  `RequiredRepFaction` int(11) unsigned NOT NULL DEFAULT '0',
  `RequiredRepValue` int(11) unsigned NOT NULL DEFAULT '0',
  `LimitTime` int(11) unsigned NOT NULL DEFAULT '0',
  `SpecialFlags` int(11) unsigned NOT NULL DEFAULT '0',
  `PrevQuestId` int(11) unsigned NOT NULL DEFAULT '0',
  `NextQuestId` int(11) unsigned NOT NULL DEFAULT '0',
  `srcItem` int(11) unsigned NOT NULL DEFAULT '0',
  `SrcItemCount` int(11) unsigned NOT NULL DEFAULT '0',
  `Title` text NOT NULL,
  `Details` text NOT NULL,
  `Objectives` text NOT NULL,
  `CompletionText` text NOT NULL,
  `IncompleteText` text NOT NULL,
  `EndText` text NOT NULL,
  `ObjectiveText1` text NOT NULL,
  `ObjectiveText2` text NOT NULL,
  `ObjectiveText3` text NOT NULL,
  `ObjectiveText4` text NOT NULL,
  `ReqItemId1` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemId2` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemId3` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemId4` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqItemCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId1` int(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId2` int(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId3` int(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOId4` int(11) NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `ReqKillMobOrGOCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId5` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemId6` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount5` int(11) unsigned NOT NULL DEFAULT '0',
  `RewChoiceItemCount6` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemId4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount3` int(11) unsigned NOT NULL DEFAULT '0',
  `RewItemCount4` int(11) unsigned NOT NULL DEFAULT '0',
  `RewRepFaction1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewRepFaction2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewRepValue1` int(11) unsigned NOT NULL DEFAULT '0',
  `RewRepValue2` int(11) unsigned NOT NULL DEFAULT '0',
  `RewMoney` int(11) unsigned NOT NULL DEFAULT '0',
  `RewXP` int(11) unsigned NOT NULL DEFAULT '0',
  `RewSpell` int(11) unsigned NOT NULL DEFAULT '0',
  `CastSpell` int(11) NOT NULL DEFAULT '0',
  `PointMapId` int(11) unsigned NOT NULL DEFAULT '0',
  `PointX` float NOT NULL DEFAULT '0',
  `PointY` float NOT NULL DEFAULT '0',
  `PointOpt` int(2) unsigned NOT NULL DEFAULT '0',
  `RequiredMoney` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger1` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger2` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger3` int(11) NOT NULL DEFAULT '0',
  `ExploreTrigger4` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest1` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest2` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest3` int(11) NOT NULL DEFAULT '0',
  `RequiredQuest4` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId1` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId2` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId3` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemId4` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount1` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount2` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount3` int(11) NOT NULL DEFAULT '0',
  `ReceiveItemCount4` int(11) NOT NULL DEFAULT '0',
  `IsRepeatable` int(2) NOT NULL DEFAULT '0',
  `reward_xp_as_money` int(6) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of quests
-- ----------------------------
INSERT INTO `quests` VALUES ('1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'test', 'test', 'test', 'test', 'test', 'test', 'test', ' ', ' ', ' ', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `recall`
-- ----------------------------
DROP TABLE IF EXISTS `recall`;
CREATE TABLE `recall` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `locname` varchar(10) NOT NULL DEFAULT '',
  `mapid` mediumint(8) NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=52 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of recall
-- ----------------------------
INSERT INTO `recall` VALUES ('1', 'sunr', '1', '-180.949', '-296.467', '11.5384');
INSERT INTO `recall` VALUES ('3', 'thun', '1', '-1196.22', '29.0941', '176.949');
INSERT INTO `recall` VALUES ('4', 'darn', '1', '9951.52', '2280.32', '1341.39');
INSERT INTO `recall` VALUES ('5', 'cross', '1', '-443.128', '-2598.87', '96.2114');
INSERT INTO `recall` VALUES ('6', 'orgr', '1', '1676.21', '-4315.29', '61.5293');
INSERT INTO `recall` VALUES ('7', 'neth', '0', '-10996.9', '-3427.67', '61.996');
INSERT INTO `recall` VALUES ('8', 'thel', '0', '-5395.57', '-3015.79', '327.58');
INSERT INTO `recall` VALUES ('9', 'storm', '0', '-8913.23', '554.633', '93.7944');
INSERT INTO `recall` VALUES ('10', 'iron', '0', '-4981.25', '-881.542', '501.66');
INSERT INTO `recall` VALUES ('11', 'oldiron', '0', '-4843.94', '-1064.63', '502.04');
INSERT INTO `recall` VALUES ('12', 'under', '0', '1586.48', '239.562', '-52.149');
INSERT INTO `recall` VALUES ('13', 'gmisl', '1', '16222.1', '16252.1', '12.5872');
INSERT INTO `recall` VALUES ('14', 'desi', '451', '16303.5', '-16173.5', '40.4365');
INSERT INTO `recall` VALUES ('15', 'prog', '451', '16391.8', '16341.2', '69.44');
INSERT INTO `recall` VALUES ('16', 'darn', '1', '10037.6', '2496.8', '1318.4');
INSERT INTO `recall` VALUES ('17', 'auberdine', '1', '6497.35', '788.197', '8.15309');
INSERT INTO `recall` VALUES ('18', 'exodar', '530', '-4003.11', '-11875.4', '-0.748712');
INSERT INTO `recall` VALUES ('19', 'silvermoon', '530', '9408.76', '-7277.49', '14.1932');
INSERT INTO `recall` VALUES ('20', 'menethil', '0', '-3771.26', '-732.714', '8.08046');
INSERT INTO `recall` VALUES ('21', 'gromgol', '0', '-12426.2', '216.954', '31.2917');
INSERT INTO `recall` VALUES ('22', 'bootybay', '0', '-14295.8', '523.848', '8.83148');
INSERT INTO `recall` VALUES ('23', 'pvparena', '0', '-13226.3', '232.452', '33.3056');
INSERT INTO `recall` VALUES ('24', 'MCore', '409', '1079.49', '-472.869', '-107.618');
INSERT INTO `recall` VALUES ('25', 'darkportal', '0', '-11853.1', '-3201.72', '-28.0021');
INSERT INTO `recall` VALUES ('26', 'Rag', '409', '749.271', '-739.457', '-213.93');
INSERT INTO `recall` VALUES ('27', 'Vael', '469', '-7512.68', '-1032.16', '408.586');
INSERT INTO `recall` VALUES ('28', 'Nef', '469', '-7529.8', '-1283.53', '476.799');
INSERT INTO `recall` VALUES ('29', 'goldshire', '0', '-9461.96', '61.7461', '55.8598');
INSERT INTO `recall` VALUES ('30', 'northshire', '0', '-8946.27', '-136.768', '83.7322');
INSERT INTO `recall` VALUES ('31', 'arena', '0', '-13282', '123.899', '25.7096');
INSERT INTO `recall` VALUES ('32', 'Outlands', '530', '-246.724', '956.06', '84.3575');
INSERT INTO `recall` VALUES ('33', 'VanCleef', '0', '-11208.2', '1676.35', '24.5614');
INSERT INTO `recall` VALUES ('34', 'S-Arena1', '1', '2958.76', '-4794.2', '235.976');
INSERT INTO `recall` VALUES ('35', 'oldif', '0', '-4821.02', '-977.204', '464.71');
INSERT INTO `recall` VALUES ('36', 'ashen', '1', '6410.85', '537.733', '13.66');
INSERT INTO `recall` VALUES ('37', 'astranaar', '1', '2806.67', '-269.968', '107.092');
INSERT INTO `recall` VALUES ('38', 'nijels', '1', '247.606', '1250.49', '192.166');
INSERT INTO `recall` VALUES ('39', 'feathermoo', '1', '-4371.86', '3289.06', '13.5693');
INSERT INTO `recall` VALUES ('40', 'bwl', '469', '-7644.86', '-1087.15', '407.859');
INSERT INTO `recall` VALUES ('41', 'epl', '0', '2282.71', '-5308.8', '87.0337');
INSERT INTO `recall` VALUES ('42', 'naxx', '0', '3105.04', '-3718.22', '133.376');
INSERT INTO `recall` VALUES ('44', 'botanica', '530', '3346.05', '1534.27', '179.689');
INSERT INTO `recall` VALUES ('45', 'coilfang', '530', '727.109', '6850.94', '-67.8074');
INSERT INTO `recall` VALUES ('46', 'strmspr', '530', '4196.62', '3011.49', '339.309');
INSERT INTO `recall` VALUES ('47', 'mulgore', '1', '-849.909', '-53.1284', '-13.1069');
INSERT INTO `recall` VALUES ('48', 'westfall', '0', '-10435.1', '1143.32', '38.335');
INSERT INTO `recall` VALUES ('51', 'uberjail', '1', '-8432.63', '1510.86', '31.9076');
INSERT INTO `recall` VALUES ('50', 'CoT', '1', '-8471.13', '-4236.79', '-194.851');

-- ----------------------------
-- Table structure for `reputation_creature_onkill`
-- ----------------------------
DROP TABLE IF EXISTS `reputation_creature_onkill`;
CREATE TABLE `reputation_creature_onkill` (
  `creature_id` int(30) NOT NULL,
  `faction_change_alliance` int(30) NOT NULL,
  `change_deltamin_alliance` int(30) NOT NULL,
  `change_deltamax_alliance` int(30) NOT NULL,
  `faction_change_horde` int(30) NOT NULL,
  `change_deltamin_horde` int(30) NOT NULL,
  `change_deltamax_horde` int(30) NOT NULL,
  KEY `index` (`creature_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of reputation_creature_onkill
-- ----------------------------

-- ----------------------------
-- Table structure for `reputation_faction_onkill`
-- ----------------------------
DROP TABLE IF EXISTS `reputation_faction_onkill`;
CREATE TABLE `reputation_faction_onkill` (
  `faction_id` int(30) NOT NULL,
  `change_factionid_alliance` int(30) NOT NULL,
  `change_deltamin_alliance` int(30) NOT NULL,
  `change_deltamax_alliance` int(30) NOT NULL,
  `change_factionid_horde` int(30) NOT NULL,
  `change_deltamin_horde` int(30) NOT NULL,
  `change_deltamax_horde` int(30) NOT NULL,
  KEY `factindex` (`faction_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of reputation_faction_onkill
-- ----------------------------

-- ----------------------------
-- Table structure for `reputation_instance_onkill`
-- ----------------------------
DROP TABLE IF EXISTS `reputation_instance_onkill`;
CREATE TABLE `reputation_instance_onkill` (
  `mapid` int(30) NOT NULL,
  `mob_rep_reward` int(30) NOT NULL,
  `mob_rep_limit` int(30) NOT NULL,
  `boss_rep_reward` int(30) NOT NULL,
  `boss_rep_limit` int(30) NOT NULL,
  `faction_change_alliance` int(30) NOT NULL,
  `faction_change_horde` int(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of reputation_instance_onkill
-- ----------------------------

-- ----------------------------
-- Table structure for `skinningloot`
-- ----------------------------
DROP TABLE IF EXISTS `skinningloot`;
CREATE TABLE `skinningloot` (
  `index` int(11) NOT NULL AUTO_INCREMENT,
  `entryid` int(10) unsigned NOT NULL DEFAULT '0',
  `itemid` int(10) unsigned NOT NULL DEFAULT '0',
  `percentchance` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`index`),
  UNIQUE KEY `index` (`index`)
) ENGINE=MyISAM AUTO_INCREMENT=2911 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of skinningloot
-- ----------------------------

-- ----------------------------
-- Table structure for `social`
-- ----------------------------
DROP TABLE IF EXISTS `social`;
CREATE TABLE `social` (
  `guid` int(6) NOT NULL DEFAULT '0',
  `socialguid` int(6) NOT NULL DEFAULT '0',
  `flags` varchar(21) NOT NULL DEFAULT '',
  `noticed` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`guid`,`socialguid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of social
-- ----------------------------

-- ----------------------------
-- Table structure for `spellextra`
-- ----------------------------
DROP TABLE IF EXISTS `spellextra`;
CREATE TABLE `spellextra` (
  `Id` int(32) NOT NULL AUTO_INCREMENT,
  `specialtype` int(32) DEFAULT NULL,
  `enchantableslots` int(32) DEFAULT NULL,
  `ExtraFlags` int(32) DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM AUTO_INCREMENT=39417 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of spellextra
-- ----------------------------
INSERT INTO `spellextra` VALUES ('13163', '4', null, null);
INSERT INTO `spellextra` VALUES ('13165', '4', null, null);
INSERT INTO `spellextra` VALUES ('14318', '4', null, null);
INSERT INTO `spellextra` VALUES ('5118', '4', null, null);
INSERT INTO `spellextra` VALUES ('14319', '4', null, null);
INSERT INTO `spellextra` VALUES ('13161', '4', null, null);
INSERT INTO `spellextra` VALUES ('14320', '4', null, null);
INSERT INTO `spellextra` VALUES ('13159', '4', null, null);
INSERT INTO `spellextra` VALUES ('20043', '4', null, null);
INSERT INTO `spellextra` VALUES ('14321', '4', null, null);
INSERT INTO `spellextra` VALUES ('20190', '4', null, null);
INSERT INTO `spellextra` VALUES ('14322', '4', null, null);
INSERT INTO `spellextra` VALUES ('25296', '4', null, null);
INSERT INTO `spellextra` VALUES ('1978', '5', null, null);
INSERT INTO `spellextra` VALUES ('13549', '5', null, null);
INSERT INTO `spellextra` VALUES ('13550', '5', null, null);
INSERT INTO `spellextra` VALUES ('3043', '5', null, null);
INSERT INTO `spellextra` VALUES ('13551', '5', null, null);
INSERT INTO `spellextra` VALUES ('14275', '5', null, null);
INSERT INTO `spellextra` VALUES ('13552', '5', null, null);
INSERT INTO `spellextra` VALUES ('30493', null, null, '1');
INSERT INTO `spellextra` VALUES ('33808', null, null, '1');
INSERT INTO `spellextra` VALUES ('3018', null, null, '1');
INSERT INTO `spellextra` VALUES ('2764', null, null, '1');
INSERT INTO `spellextra` VALUES ('5019', null, null, '1');
INSERT INTO `spellextra` VALUES ('5938', null, null, '1');
INSERT INTO `spellextra` VALUES ('5940', null, null, '1');
INSERT INTO `spellextra` VALUES ('26741', null, null, '1');
INSERT INTO `spellextra` VALUES ('26679', null, null, '1');
INSERT INTO `spellextra` VALUES ('37074', null, null, '1');
INSERT INTO `spellextra` VALUES ('32645', null, null, '1');
INSERT INTO `spellextra` VALUES ('32684', null, null, '1');
INSERT INTO `spellextra` VALUES ('408', null, null, '1');
INSERT INTO `spellextra` VALUES ('8643', null, null, '1');
INSERT INTO `spellextra` VALUES ('27615', null, null, '1');
INSERT INTO `spellextra` VALUES ('30621', null, null, '1');
INSERT INTO `spellextra` VALUES ('30832', null, null, '1');
INSERT INTO `spellextra` VALUES ('32864', null, null, '1');
INSERT INTO `spellextra` VALUES ('16511', null, null, '1');
INSERT INTO `spellextra` VALUES ('17347', null, null, '1');
INSERT INTO `spellextra` VALUES ('17348', null, null, '1');
INSERT INTO `spellextra` VALUES ('26864', null, null, '1');
INSERT INTO `spellextra` VALUES ('30478', null, null, '1');
INSERT INTO `spellextra` VALUES ('37331', null, null, '1');
INSERT INTO `spellextra` VALUES ('1943', null, null, '1');
INSERT INTO `spellextra` VALUES ('8639', null, null, '1');
INSERT INTO `spellextra` VALUES ('8640', null, null, '1');
INSERT INTO `spellextra` VALUES ('11273', null, null, '1');
INSERT INTO `spellextra` VALUES ('11274', null, null, '1');
INSERT INTO `spellextra` VALUES ('11275', null, null, '1');
INSERT INTO `spellextra` VALUES ('14874', null, null, '1');
INSERT INTO `spellextra` VALUES ('14903', null, null, '1');
INSERT INTO `spellextra` VALUES ('15583', null, null, '1');
INSERT INTO `spellextra` VALUES ('26867', null, null, '1');
INSERT INTO `spellextra` VALUES ('8647', null, null, '1');
INSERT INTO `spellextra` VALUES ('8649', null, null, '1');
INSERT INTO `spellextra` VALUES ('8650', null, null, '1');
INSERT INTO `spellextra` VALUES ('11197', null, null, '1');
INSERT INTO `spellextra` VALUES ('11198', null, null, '1');
INSERT INTO `spellextra` VALUES ('26866', null, null, '1');
INSERT INTO `spellextra` VALUES ('30965', null, null, '1');
INSERT INTO `spellextra` VALUES ('8818', null, null, '1');
INSERT INTO `spellextra` VALUES ('28911', null, null, '1');
INSERT INTO `spellextra` VALUES ('29433', null, null, '1');
INSERT INTO `spellextra` VALUES ('37066', null, null, '1');
INSERT INTO `spellextra` VALUES ('1766', null, null, '1');
INSERT INTO `spellextra` VALUES ('1767', null, null, '1');
INSERT INTO `spellextra` VALUES ('1768', null, null, '1');
INSERT INTO `spellextra` VALUES ('1769', null, null, '1');
INSERT INTO `spellextra` VALUES ('11978', null, null, '1');
INSERT INTO `spellextra` VALUES ('15610', null, null, '1');
INSERT INTO `spellextra` VALUES ('15614', null, null, '1');
INSERT INTO `spellextra` VALUES ('17748', null, null, '1');
INSERT INTO `spellextra` VALUES ('18425', null, null, '1');
INSERT INTO `spellextra` VALUES ('27613', null, null, '1');
INSERT INTO `spellextra` VALUES ('27814', null, null, '1');
INSERT INTO `spellextra` VALUES ('29560', null, null, '1');
INSERT INTO `spellextra` VALUES ('29586', null, null, '1');
INSERT INTO `spellextra` VALUES ('30460', null, null, '1');
INSERT INTO `spellextra` VALUES ('31402', null, null, '1');
INSERT INTO `spellextra` VALUES ('32105', null, null, '1');
INSERT INTO `spellextra` VALUES ('33424', null, null, '1');
INSERT INTO `spellextra` VALUES ('34802', null, null, '1');
INSERT INTO `spellextra` VALUES ('36033', null, null, '1');
INSERT INTO `spellextra` VALUES ('38625', null, null, '1');
INSERT INTO `spellextra` VALUES ('38768', null, null, '1');
INSERT INTO `spellextra` VALUES ('39043', null, null, '1');
INSERT INTO `spellextra` VALUES ('5171', null, null, '1');
INSERT INTO `spellextra` VALUES ('6434', null, null, '1');
INSERT INTO `spellextra` VALUES ('6774', null, null, '1');
INSERT INTO `spellextra` VALUES ('30470', null, null, '1');
INSERT INTO `spellextra` VALUES ('2070', null, null, '1');
INSERT INTO `spellextra` VALUES ('6770', null, null, '1');
INSERT INTO `spellextra` VALUES ('11297', null, null, '1');
INSERT INTO `spellextra` VALUES ('30980', null, null, '1');
INSERT INTO `spellextra` VALUES ('1776', null, null, '1');
INSERT INTO `spellextra` VALUES ('1777', null, null, '1');
INSERT INTO `spellextra` VALUES ('3232', null, null, '1');
INSERT INTO `spellextra` VALUES ('8629', null, null, '1');
INSERT INTO `spellextra` VALUES ('11285', null, null, '1');
INSERT INTO `spellextra` VALUES ('11286', null, null, '1');
INSERT INTO `spellextra` VALUES ('12540', null, null, '1');
INSERT INTO `spellextra` VALUES ('13579', null, null, '1');
INSERT INTO `spellextra` VALUES ('24698', null, null, '1');
INSERT INTO `spellextra` VALUES ('28456', null, null, '1');
INSERT INTO `spellextra` VALUES ('29425', null, null, '1');
INSERT INTO `spellextra` VALUES ('34940', null, null, '1');
INSERT INTO `spellextra` VALUES ('36862', null, null, '1');
INSERT INTO `spellextra` VALUES ('38764', null, null, '1');
INSERT INTO `spellextra` VALUES ('38863', null, null, '1');
INSERT INTO `spellextra` VALUES ('921', null, null, '1');
INSERT INTO `spellextra` VALUES ('1804', null, null, '1');
INSERT INTO `spellextra` VALUES ('1805', null, null, '1');
INSERT INTO `spellextra` VALUES ('1806', null, null, '1');
INSERT INTO `spellextra` VALUES ('6461', null, null, '1');
INSERT INTO `spellextra` VALUES ('6463', null, null, '1');
INSERT INTO `spellextra` VALUES ('2098', null, null, '1');
INSERT INTO `spellextra` VALUES ('6760', null, null, '1');
INSERT INTO `spellextra` VALUES ('6761', null, null, '1');
INSERT INTO `spellextra` VALUES ('6762', null, null, '1');
INSERT INTO `spellextra` VALUES ('8623', null, null, '1');
INSERT INTO `spellextra` VALUES ('8624', null, null, '1');
INSERT INTO `spellextra` VALUES ('11299', null, null, '1');
INSERT INTO `spellextra` VALUES ('11300', null, null, '1');
INSERT INTO `spellextra` VALUES ('15691', null, null, '1');
INSERT INTO `spellextra` VALUES ('15692', null, null, '1');
INSERT INTO `spellextra` VALUES ('26865', null, null, '1');
INSERT INTO `spellextra` VALUES ('27611', null, null, '1');
INSERT INTO `spellextra` VALUES ('31016', null, null, '1');
INSERT INTO `spellextra` VALUES ('1752', null, null, '1');
INSERT INTO `spellextra` VALUES ('1757', null, null, '1');
INSERT INTO `spellextra` VALUES ('1758', null, null, '1');
INSERT INTO `spellextra` VALUES ('1759', null, null, '1');
INSERT INTO `spellextra` VALUES ('1760', null, null, '1');
INSERT INTO `spellextra` VALUES ('8621', null, null, '1');
INSERT INTO `spellextra` VALUES ('11293', null, null, '1');
INSERT INTO `spellextra` VALUES ('11294', null, null, '1');
INSERT INTO `spellextra` VALUES ('14873', null, null, '1');
INSERT INTO `spellextra` VALUES ('15581', null, null, '1');
INSERT INTO `spellextra` VALUES ('15667', null, null, '1');
INSERT INTO `spellextra` VALUES ('19472', null, null, '1');
INSERT INTO `spellextra` VALUES ('24824', null, null, '1');
INSERT INTO `spellextra` VALUES ('26861', null, null, '1');
INSERT INTO `spellextra` VALUES ('26862', null, null, '1');
INSERT INTO `spellextra` VALUES ('32217', null, null, '1');
INSERT INTO `spellextra` VALUES ('34428', null, null, '1');
INSERT INTO `spellextra` VALUES ('20243', null, null, '1');
INSERT INTO `spellextra` VALUES ('30016', null, null, '1');
INSERT INTO `spellextra` VALUES ('30017', null, null, '1');
INSERT INTO `spellextra` VALUES ('30022', null, null, '1');
INSERT INTO `spellextra` VALUES ('36891', null, null, '1');
INSERT INTO `spellextra` VALUES ('36894', null, null, '1');
INSERT INTO `spellextra` VALUES ('38849', null, null, '1');
INSERT INTO `spellextra` VALUES ('38967', null, null, '1');
INSERT INTO `spellextra` VALUES ('8242', null, null, '1');
INSERT INTO `spellextra` VALUES ('15655', null, null, '1');
INSERT INTO `spellextra` VALUES ('23922', null, null, '1');
INSERT INTO `spellextra` VALUES ('23923', null, null, '1');
INSERT INTO `spellextra` VALUES ('23924', null, null, '1');
INSERT INTO `spellextra` VALUES ('23925', null, null, '1');
INSERT INTO `spellextra` VALUES ('25258', null, null, '1');
INSERT INTO `spellextra` VALUES ('29684', null, null, '1');
INSERT INTO `spellextra` VALUES ('30356', null, null, '1');
INSERT INTO `spellextra` VALUES ('30688', null, null, '1');
INSERT INTO `spellextra` VALUES ('12331', null, null, '1');
INSERT INTO `spellextra` VALUES ('23880', null, null, '1');
INSERT INTO `spellextra` VALUES ('23881', null, null, '1');
INSERT INTO `spellextra` VALUES ('23885', null, null, '1');
INSERT INTO `spellextra` VALUES ('23886', null, null, '1');
INSERT INTO `spellextra` VALUES ('23887', null, null, '1');
INSERT INTO `spellextra` VALUES ('23888', null, null, '1');
INSERT INTO `spellextra` VALUES ('23889', null, null, '1');
INSERT INTO `spellextra` VALUES ('23890', null, null, '1');
INSERT INTO `spellextra` VALUES ('23891', null, null, '1');
INSERT INTO `spellextra` VALUES ('23892', null, null, '1');
INSERT INTO `spellextra` VALUES ('23893', null, null, '1');
INSERT INTO `spellextra` VALUES ('23894', null, null, '1');
INSERT INTO `spellextra` VALUES ('25251', null, null, '1');
INSERT INTO `spellextra` VALUES ('25252', null, null, '1');
INSERT INTO `spellextra` VALUES ('25253', null, null, '1');
INSERT INTO `spellextra` VALUES ('30335', null, null, '1');
INSERT INTO `spellextra` VALUES ('30339', null, null, '1');
INSERT INTO `spellextra` VALUES ('30340', null, null, '1');
INSERT INTO `spellextra` VALUES ('30475', null, null, '1');
INSERT INTO `spellextra` VALUES ('30476', null, null, '1');
INSERT INTO `spellextra` VALUES ('31997', null, null, '1');
INSERT INTO `spellextra` VALUES ('31998', null, null, '1');
INSERT INTO `spellextra` VALUES ('35123', null, null, '1');
INSERT INTO `spellextra` VALUES ('35125', null, null, '1');
INSERT INTO `spellextra` VALUES ('35947', null, null, '1');
INSERT INTO `spellextra` VALUES ('35948', null, null, '1');
INSERT INTO `spellextra` VALUES ('39071', null, null, '1');
INSERT INTO `spellextra` VALUES ('39072', null, null, '1');
INSERT INTO `spellextra` VALUES ('9347', null, null, '1');
INSERT INTO `spellextra` VALUES ('12294', null, null, '1');
INSERT INTO `spellextra` VALUES ('13737', null, null, '1');
INSERT INTO `spellextra` VALUES ('15708', null, null, '1');
INSERT INTO `spellextra` VALUES ('16856', null, null, '1');
INSERT INTO `spellextra` VALUES ('17547', null, null, '1');
INSERT INTO `spellextra` VALUES ('19643', null, null, '1');
INSERT INTO `spellextra` VALUES ('21551', null, null, '1');
INSERT INTO `spellextra` VALUES ('21552', null, null, '1');
INSERT INTO `spellextra` VALUES ('21553', null, null, '1');
INSERT INTO `spellextra` VALUES ('24573', null, null, '1');
INSERT INTO `spellextra` VALUES ('24816', null, null, '1');
INSERT INTO `spellextra` VALUES ('25248', null, null, '1');
INSERT INTO `spellextra` VALUES ('26652', null, null, '1');
INSERT INTO `spellextra` VALUES ('27580', null, null, '1');
INSERT INTO `spellextra` VALUES ('29572', null, null, '1');
INSERT INTO `spellextra` VALUES ('30330', null, null, '1');
INSERT INTO `spellextra` VALUES ('31911', null, null, '1');
INSERT INTO `spellextra` VALUES ('32736', null, null, '1');
INSERT INTO `spellextra` VALUES ('35054', null, null, '1');
INSERT INTO `spellextra` VALUES ('37335', null, null, '1');
INSERT INTO `spellextra` VALUES ('39171', null, null, '1');
INSERT INTO `spellextra` VALUES ('6552', null, null, '1');
INSERT INTO `spellextra` VALUES ('6554', null, null, '1');
INSERT INTO `spellextra` VALUES ('6555', null, null, '1');
INSERT INTO `spellextra` VALUES ('10887', null, null, '1');
INSERT INTO `spellextra` VALUES ('12555', null, null, '1');
INSERT INTO `spellextra` VALUES ('13491', null, null, '1');
INSERT INTO `spellextra` VALUES ('15615', null, null, '1');
INSERT INTO `spellextra` VALUES ('19639', null, null, '1');
INSERT INTO `spellextra` VALUES ('25595', null, null, '1');
INSERT INTO `spellextra` VALUES ('36470', null, null, '1');
INSERT INTO `spellextra` VALUES ('38313', null, null, '1');
INSERT INTO `spellextra` VALUES ('20253', null, null, '1');
INSERT INTO `spellextra` VALUES ('20614', null, null, '1');
INSERT INTO `spellextra` VALUES ('20615', null, null, '1');
INSERT INTO `spellextra` VALUES ('25273', null, null, '1');
INSERT INTO `spellextra` VALUES ('25274', null, null, '1');
INSERT INTO `spellextra` VALUES ('27826', null, null, '1');
INSERT INTO `spellextra` VALUES ('30153', null, null, '1');
INSERT INTO `spellextra` VALUES ('30195', null, null, '1');
INSERT INTO `spellextra` VALUES ('30197', null, null, '1');
INSERT INTO `spellextra` VALUES ('1464', null, null, '1');
INSERT INTO `spellextra` VALUES ('8820', null, null, '1');
INSERT INTO `spellextra` VALUES ('11430', null, null, '1');
INSERT INTO `spellextra` VALUES ('11604', null, null, '1');
INSERT INTO `spellextra` VALUES ('11605', null, null, '1');
INSERT INTO `spellextra` VALUES ('25241', null, null, '1');
INSERT INTO `spellextra` VALUES ('25242', null, null, '1');
INSERT INTO `spellextra` VALUES ('34620', null, null, '1');
INSERT INTO `spellextra` VALUES ('6174', null, null, '1');
INSERT INTO `spellextra` VALUES ('6175', null, null, '1');
INSERT INTO `spellextra` VALUES ('7160', null, null, '1');
INSERT INTO `spellextra` VALUES ('20647', null, null, '1');
INSERT INTO `spellextra` VALUES ('25234', null, null, '1');
INSERT INTO `spellextra` VALUES ('25236', null, null, '1');
INSERT INTO `spellextra` VALUES ('26651', null, null, '1');
INSERT INTO `spellextra` VALUES ('38948', null, null, '1');
INSERT INTO `spellextra` VALUES ('38959', null, null, '1');
INSERT INTO `spellextra` VALUES ('845', null, null, '1');
INSERT INTO `spellextra` VALUES ('5480', null, null, '1');
INSERT INTO `spellextra` VALUES ('5508', null, null, '1');
INSERT INTO `spellextra` VALUES ('5532', null, null, '1');
INSERT INTO `spellextra` VALUES ('7369', null, null, '1');
INSERT INTO `spellextra` VALUES ('11427', null, null, '1');
INSERT INTO `spellextra` VALUES ('11608', null, null, '1');
INSERT INTO `spellextra` VALUES ('11609', null, null, '1');
INSERT INTO `spellextra` VALUES ('15280', null, null, '1');
INSERT INTO `spellextra` VALUES ('15284', null, null, '1');
INSERT INTO `spellextra` VALUES ('15496', null, null, '1');
INSERT INTO `spellextra` VALUES ('15579', null, null, '1');
INSERT INTO `spellextra` VALUES ('15584', null, null, '1');
INSERT INTO `spellextra` VALUES ('15613', null, null, '1');
INSERT INTO `spellextra` VALUES ('15622', null, null, '1');
INSERT INTO `spellextra` VALUES ('15623', null, null, '1');
INSERT INTO `spellextra` VALUES ('15663', null, null, '1');
INSERT INTO `spellextra` VALUES ('15754', null, null, '1');
INSERT INTO `spellextra` VALUES ('16044', null, null, '1');
INSERT INTO `spellextra` VALUES ('17685', null, null, '1');
INSERT INTO `spellextra` VALUES ('19632', null, null, '1');
INSERT INTO `spellextra` VALUES ('19642', null, null, '1');
INSERT INTO `spellextra` VALUES ('19983', null, null, '1');
INSERT INTO `spellextra` VALUES ('20569', null, null, '1');
INSERT INTO `spellextra` VALUES ('20605', null, null, '1');
INSERT INTO `spellextra` VALUES ('20666', null, null, '1');
INSERT INTO `spellextra` VALUES ('20677', null, null, '1');
INSERT INTO `spellextra` VALUES ('20684', null, null, '1');
INSERT INTO `spellextra` VALUES ('20691', null, null, '1');
INSERT INTO `spellextra` VALUES ('22540', null, null, '1');
INSERT INTO `spellextra` VALUES ('25231', null, null, '1');
INSERT INTO `spellextra` VALUES ('26350', null, null, '1');
INSERT INTO `spellextra` VALUES ('27794', null, null, '1');
INSERT INTO `spellextra` VALUES ('29561', null, null, '1');
INSERT INTO `spellextra` VALUES ('29665', null, null, '1');
INSERT INTO `spellextra` VALUES ('30014', null, null, '1');
INSERT INTO `spellextra` VALUES ('30131', null, null, '1');
INSERT INTO `spellextra` VALUES ('30213', null, null, '1');
INSERT INTO `spellextra` VALUES ('30219', null, null, '1');
INSERT INTO `spellextra` VALUES ('30223', null, null, '1');
INSERT INTO `spellextra` VALUES ('30619', null, null, '1');
INSERT INTO `spellextra` VALUES ('31043', null, null, '1');
INSERT INTO `spellextra` VALUES ('31345', null, null, '1');
INSERT INTO `spellextra` VALUES ('31779', null, null, '1');
INSERT INTO `spellextra` VALUES ('34995', null, null, '1');
INSERT INTO `spellextra` VALUES ('37476', null, null, '1');
INSERT INTO `spellextra` VALUES ('37598', null, null, '1');
INSERT INTO `spellextra` VALUES ('38260', null, null, '1');
INSERT INTO `spellextra` VALUES ('38474', null, null, '1');
INSERT INTO `spellextra` VALUES ('39047', null, null, '1');
INSERT INTO `spellextra` VALUES ('39174', null, null, '1');
INSERT INTO `spellextra` VALUES ('694', null, null, '1');
INSERT INTO `spellextra` VALUES ('7400', null, null, '1');
INSERT INTO `spellextra` VALUES ('7402', null, null, '1');
INSERT INTO `spellextra` VALUES ('20559', null, null, '1');
INSERT INTO `spellextra` VALUES ('20560', null, null, '1');
INSERT INTO `spellextra` VALUES ('21008', null, null, '1');
INSERT INTO `spellextra` VALUES ('25266', null, null, '1');
INSERT INTO `spellextra` VALUES ('6572', null, null, '1');
INSERT INTO `spellextra` VALUES ('6574', null, null, '1');
INSERT INTO `spellextra` VALUES ('7379', null, null, '1');
INSERT INTO `spellextra` VALUES ('11600', null, null, '1');
INSERT INTO `spellextra` VALUES ('11601', null, null, '1');
INSERT INTO `spellextra` VALUES ('12170', null, null, '1');
INSERT INTO `spellextra` VALUES ('19130', null, null, '1');
INSERT INTO `spellextra` VALUES ('25269', null, null, '1');
INSERT INTO `spellextra` VALUES ('25288', null, null, '1');
INSERT INTO `spellextra` VALUES ('30357', null, null, '1');
INSERT INTO `spellextra` VALUES ('37517', null, null, '1');
INSERT INTO `spellextra` VALUES ('72', null, null, '1');
INSERT INTO `spellextra` VALUES ('1671', null, null, '1');
INSERT INTO `spellextra` VALUES ('1672', null, null, '1');
INSERT INTO `spellextra` VALUES ('11972', null, null, '1');
INSERT INTO `spellextra` VALUES ('18498', null, null, '1');
INSERT INTO `spellextra` VALUES ('33871', null, null, '1');
INSERT INTO `spellextra` VALUES ('35178', null, null, '1');
INSERT INTO `spellextra` VALUES ('36988', null, null, '1');
INSERT INTO `spellextra` VALUES ('38233', null, null, '1');
INSERT INTO `spellextra` VALUES ('7384', null, null, '1');
INSERT INTO `spellextra` VALUES ('7887', null, null, '1');
INSERT INTO `spellextra` VALUES ('11584', null, null, '1');
INSERT INTO `spellextra` VALUES ('11585', null, null, '1');
INSERT INTO `spellextra` VALUES ('14895', null, null, '1');
INSERT INTO `spellextra` VALUES ('17198', null, null, '1');
INSERT INTO `spellextra` VALUES ('24407', null, null, '1');
INSERT INTO `spellextra` VALUES ('24817', null, null, '1');
INSERT INTO `spellextra` VALUES ('32154', null, null, '1');
INSERT INTO `spellextra` VALUES ('37321', null, null, '1');
INSERT INTO `spellextra` VALUES ('37529', null, null, '1');
INSERT INTO `spellextra` VALUES ('7386', null, null, '1');
INSERT INTO `spellextra` VALUES ('7405', null, null, '1');
INSERT INTO `spellextra` VALUES ('8380', null, null, '1');
INSERT INTO `spellextra` VALUES ('11596', null, null, '1');
INSERT INTO `spellextra` VALUES ('11597', null, null, '1');
INSERT INTO `spellextra` VALUES ('11971', null, null, '1');
INSERT INTO `spellextra` VALUES ('13444', null, null, '1');
INSERT INTO `spellextra` VALUES ('15502', null, null, '1');
INSERT INTO `spellextra` VALUES ('15572', null, null, '1');
INSERT INTO `spellextra` VALUES ('16145', null, null, '1');
INSERT INTO `spellextra` VALUES ('21081', null, null, '1');
INSERT INTO `spellextra` VALUES ('24317', null, null, '1');
INSERT INTO `spellextra` VALUES ('25051', null, null, '1');
INSERT INTO `spellextra` VALUES ('25225', null, null, '1');
INSERT INTO `spellextra` VALUES ('27991', null, null, '1');
INSERT INTO `spellextra` VALUES ('30901', null, null, '1');
INSERT INTO `spellextra` VALUES ('35851', null, null, '1');
INSERT INTO `spellextra` VALUES ('1715', null, null, '1');
INSERT INTO `spellextra` VALUES ('7372', null, null, '1');
INSERT INTO `spellextra` VALUES ('7373', null, null, '1');
INSERT INTO `spellextra` VALUES ('9080', null, null, '1');
INSERT INTO `spellextra` VALUES ('25212', null, null, '1');
INSERT INTO `spellextra` VALUES ('26141', null, null, '1');
INSERT INTO `spellextra` VALUES ('26211', null, null, '1');
INSERT INTO `spellextra` VALUES ('27584', null, null, '1');
INSERT INTO `spellextra` VALUES ('29667', null, null, '1');
INSERT INTO `spellextra` VALUES ('30989', null, null, '1');
INSERT INTO `spellextra` VALUES ('31553', null, null, '1');
INSERT INTO `spellextra` VALUES ('38262', null, null, '1');
INSERT INTO `spellextra` VALUES ('38995', null, null, '1');
INSERT INTO `spellextra` VALUES ('20508', null, null, '1');
INSERT INTO `spellextra` VALUES ('22120', null, null, '1');
INSERT INTO `spellextra` VALUES ('22911', null, null, '1');
INSERT INTO `spellextra` VALUES ('24193', null, null, '1');
INSERT INTO `spellextra` VALUES ('24408', null, null, '1');
INSERT INTO `spellextra` VALUES ('25821', null, null, '1');
INSERT INTO `spellextra` VALUES ('29320', null, null, '1');
INSERT INTO `spellextra` VALUES ('31733', null, null, '1');
INSERT INTO `spellextra` VALUES ('32323', null, null, '1');
INSERT INTO `spellextra` VALUES ('33709', null, null, '1');
INSERT INTO `spellextra` VALUES ('34846', null, null, '1');
INSERT INTO `spellextra` VALUES ('35412', null, null, '1');
INSERT INTO `spellextra` VALUES ('35570', null, null, '1');
INSERT INTO `spellextra` VALUES ('35754', null, null, '1');
INSERT INTO `spellextra` VALUES ('36058', null, null, '1');
INSERT INTO `spellextra` VALUES ('36140', null, null, '1');
INSERT INTO `spellextra` VALUES ('36509', null, null, '1');
INSERT INTO `spellextra` VALUES ('37511', null, null, '1');
INSERT INTO `spellextra` VALUES ('38461', null, null, '1');
INSERT INTO `spellextra` VALUES ('772', null, null, '1');
INSERT INTO `spellextra` VALUES ('6546', null, null, '1');
INSERT INTO `spellextra` VALUES ('6547', null, null, '1');
INSERT INTO `spellextra` VALUES ('6548', null, null, '1');
INSERT INTO `spellextra` VALUES ('11572', null, null, '1');
INSERT INTO `spellextra` VALUES ('11573', null, null, '1');
INSERT INTO `spellextra` VALUES ('11574', null, null, '1');
INSERT INTO `spellextra` VALUES ('11977', null, null, '1');
INSERT INTO `spellextra` VALUES ('12054', null, null, '1');
INSERT INTO `spellextra` VALUES ('13318', null, null, '1');
INSERT INTO `spellextra` VALUES ('13443', null, null, '1');
INSERT INTO `spellextra` VALUES ('13445', null, null, '1');
INSERT INTO `spellextra` VALUES ('13738', null, null, '1');
INSERT INTO `spellextra` VALUES ('14087', null, null, '1');
INSERT INTO `spellextra` VALUES ('14118', null, null, '1');
INSERT INTO `spellextra` VALUES ('16393', null, null, '1');
INSERT INTO `spellextra` VALUES ('16403', null, null, '1');
INSERT INTO `spellextra` VALUES ('16406', null, null, '1');
INSERT INTO `spellextra` VALUES ('16509', null, null, '1');
INSERT INTO `spellextra` VALUES ('17153', null, null, '1');
INSERT INTO `spellextra` VALUES ('17504', null, null, '1');
INSERT INTO `spellextra` VALUES ('18075', null, null, '1');
INSERT INTO `spellextra` VALUES ('18078', null, null, '1');
INSERT INTO `spellextra` VALUES ('18106', null, null, '1');
INSERT INTO `spellextra` VALUES ('18200', null, null, '1');
INSERT INTO `spellextra` VALUES ('18202', null, null, '1');
INSERT INTO `spellextra` VALUES ('21949', null, null, '1');
INSERT INTO `spellextra` VALUES ('25208', null, null, '1');
INSERT INTO `spellextra` VALUES ('29574', null, null, '1');
INSERT INTO `spellextra` VALUES ('29578', null, null, '1');
INSERT INTO `spellextra` VALUES ('36965', null, null, '1');
INSERT INTO `spellextra` VALUES ('36991', null, null, '1');
INSERT INTO `spellextra` VALUES ('37662', null, null, '1');
INSERT INTO `spellextra` VALUES ('78', null, null, '1');
INSERT INTO `spellextra` VALUES ('284', null, null, '1');
INSERT INTO `spellextra` VALUES ('285', null, null, '1');
INSERT INTO `spellextra` VALUES ('1608', null, null, '1');
INSERT INTO `spellextra` VALUES ('11564', null, null, '1');
INSERT INTO `spellextra` VALUES ('11565', null, null, '1');
INSERT INTO `spellextra` VALUES ('11566', null, null, '1');
INSERT INTO `spellextra` VALUES ('11567', null, null, '1');
INSERT INTO `spellextra` VALUES ('25286', null, null, '1');
INSERT INTO `spellextra` VALUES ('25710', null, null, '1');
INSERT INTO `spellextra` VALUES ('25712', null, null, '1');
INSERT INTO `spellextra` VALUES ('29426', null, null, '1');
INSERT INTO `spellextra` VALUES ('29567', null, null, '1');
INSERT INTO `spellextra` VALUES ('29707', null, null, '1');
INSERT INTO `spellextra` VALUES ('30324', null, null, '1');
INSERT INTO `spellextra` VALUES ('31827', null, null, '1');
INSERT INTO `spellextra` VALUES ('421', null, null, '1');
INSERT INTO `spellextra` VALUES ('930', null, null, '1');
INSERT INTO `spellextra` VALUES ('2860', null, null, '1');
INSERT INTO `spellextra` VALUES ('10605', null, null, '1');
INSERT INTO `spellextra` VALUES ('12058', null, null, '1');
INSERT INTO `spellextra` VALUES ('15117', null, null, '1');
INSERT INTO `spellextra` VALUES ('15305', null, null, '1');
INSERT INTO `spellextra` VALUES ('15659', null, null, '1');
INSERT INTO `spellextra` VALUES ('16006', null, null, '1');
INSERT INTO `spellextra` VALUES ('16033', null, null, '1');
INSERT INTO `spellextra` VALUES ('16921', null, null, '1');
INSERT INTO `spellextra` VALUES ('20831', null, null, '1');
INSERT INTO `spellextra` VALUES ('21179', null, null, '1');
INSERT INTO `spellextra` VALUES ('22355', null, null, '1');
INSERT INTO `spellextra` VALUES ('23106', null, null, '1');
INSERT INTO `spellextra` VALUES ('23206', null, null, '1');
INSERT INTO `spellextra` VALUES ('24680', null, null, '1');
INSERT INTO `spellextra` VALUES ('25021', null, null, '1');
INSERT INTO `spellextra` VALUES ('25439', null, null, '1');
INSERT INTO `spellextra` VALUES ('25442', null, null, '1');
INSERT INTO `spellextra` VALUES ('27567', null, null, '1');
INSERT INTO `spellextra` VALUES ('28167', null, null, '1');
INSERT INTO `spellextra` VALUES ('28293', null, null, '1');
INSERT INTO `spellextra` VALUES ('28900', null, null, '1');
INSERT INTO `spellextra` VALUES ('31330', null, null, '1');
INSERT INTO `spellextra` VALUES ('31717', null, null, '1');
INSERT INTO `spellextra` VALUES ('32337', null, null, '1');
INSERT INTO `spellextra` VALUES ('33643', null, null, '1');
INSERT INTO `spellextra` VALUES ('36896', null, null, '1');
INSERT INTO `spellextra` VALUES ('37448', null, null, '1');
INSERT INTO `spellextra` VALUES ('39066', null, null, '1');
INSERT INTO `spellextra` VALUES ('8056', null, null, '1');
INSERT INTO `spellextra` VALUES ('8058', null, null, '1');
INSERT INTO `spellextra` VALUES ('10472', null, null, '1');
INSERT INTO `spellextra` VALUES ('10473', null, null, '1');
INSERT INTO `spellextra` VALUES ('12548', null, null, '1');
INSERT INTO `spellextra` VALUES ('15089', null, null, '1');
INSERT INTO `spellextra` VALUES ('15499', null, null, '1');
INSERT INTO `spellextra` VALUES ('19133', null, null, '1');
INSERT INTO `spellextra` VALUES ('21030', null, null, '1');
INSERT INTO `spellextra` VALUES ('21401', null, null, '1');
INSERT INTO `spellextra` VALUES ('22582', null, null, '1');
INSERT INTO `spellextra` VALUES ('23115', null, null, '1');
INSERT INTO `spellextra` VALUES ('25464', null, null, '1');
INSERT INTO `spellextra` VALUES ('29666', null, null, '1');
INSERT INTO `spellextra` VALUES ('34353', null, null, '1');
INSERT INTO `spellextra` VALUES ('37332', null, null, '1');
INSERT INTO `spellextra` VALUES ('37865', null, null, '1');
INSERT INTO `spellextra` VALUES ('38234', null, null, '1');
INSERT INTO `spellextra` VALUES ('39062', null, null, '1');
INSERT INTO `spellextra` VALUES ('370', null, null, '1');
INSERT INTO `spellextra` VALUES ('8012', null, null, '1');
INSERT INTO `spellextra` VALUES ('25756', null, null, '1');
INSERT INTO `spellextra` VALUES ('27626', null, null, '1');
INSERT INTO `spellextra` VALUES ('33625', null, null, '1');
INSERT INTO `spellextra` VALUES ('8050', null, null, '1');
INSERT INTO `spellextra` VALUES ('8052', null, null, '1');
INSERT INTO `spellextra` VALUES ('8053', null, null, '1');
INSERT INTO `spellextra` VALUES ('10447', null, null, '1');
INSERT INTO `spellextra` VALUES ('10448', null, null, '1');
INSERT INTO `spellextra` VALUES ('13729', null, null, '1');
INSERT INTO `spellextra` VALUES ('15039', null, null, '1');
INSERT INTO `spellextra` VALUES ('15096', null, null, '1');
INSERT INTO `spellextra` VALUES ('15616', null, null, '1');
INSERT INTO `spellextra` VALUES ('16804', null, null, '1');
INSERT INTO `spellextra` VALUES ('22423', null, null, '1');
INSERT INTO `spellextra` VALUES ('23038', null, null, '1');
INSERT INTO `spellextra` VALUES ('25456', null, null, '1');
INSERT INTO `spellextra` VALUES ('25457', null, null, '1');
INSERT INTO `spellextra` VALUES ('29228', null, null, '1');
INSERT INTO `spellextra` VALUES ('32967', null, null, '1');
INSERT INTO `spellextra` VALUES ('34354', null, null, '1');
INSERT INTO `spellextra` VALUES ('8042', null, null, '1');
INSERT INTO `spellextra` VALUES ('8044', null, null, '1');
INSERT INTO `spellextra` VALUES ('8045', null, null, '1');
INSERT INTO `spellextra` VALUES ('8046', null, null, '1');
INSERT INTO `spellextra` VALUES ('10412', null, null, '1');
INSERT INTO `spellextra` VALUES ('10413', null, null, '1');
INSERT INTO `spellextra` VALUES ('10414', null, null, '1');
INSERT INTO `spellextra` VALUES ('13281', null, null, '1');
INSERT INTO `spellextra` VALUES ('13728', null, null, '1');
INSERT INTO `spellextra` VALUES ('15501', null, null, '1');
INSERT INTO `spellextra` VALUES ('22885', null, null, '1');
INSERT INTO `spellextra` VALUES ('23114', null, null, '1');
INSERT INTO `spellextra` VALUES ('24685', null, null, '1');
INSERT INTO `spellextra` VALUES ('25025', null, null, '1');
INSERT INTO `spellextra` VALUES ('25454', null, null, '1');
INSERT INTO `spellextra` VALUES ('26194', null, null, '1');
INSERT INTO `spellextra` VALUES ('34914', null, null, '1');
INSERT INTO `spellextra` VALUES ('34916', null, null, '1');
INSERT INTO `spellextra` VALUES ('34917', null, null, '1');
INSERT INTO `spellextra` VALUES ('34918', null, null, '1');
INSERT INTO `spellextra` VALUES ('34919', null, null, '1');
INSERT INTO `spellextra` VALUES ('2691', null, null, '1');
INSERT INTO `spellextra` VALUES ('8129', null, null, '1');
INSERT INTO `spellextra` VALUES ('8131', null, null, '1');
INSERT INTO `spellextra` VALUES ('10874', null, null, '1');
INSERT INTO `spellextra` VALUES ('10875', null, null, '1');
INSERT INTO `spellextra` VALUES ('10876', null, null, '1');
INSERT INTO `spellextra` VALUES ('11981', null, null, '1');
INSERT INTO `spellextra` VALUES ('12745', null, null, '1');
INSERT INTO `spellextra` VALUES ('13321', null, null, '1');
INSERT INTO `spellextra` VALUES ('14033', null, null, '1');
INSERT INTO `spellextra` VALUES ('15785', null, null, '1');
INSERT INTO `spellextra` VALUES ('15800', null, null, '1');
INSERT INTO `spellextra` VALUES ('15980', null, null, '1');
INSERT INTO `spellextra` VALUES ('17615', null, null, '1');
INSERT INTO `spellextra` VALUES ('17630', null, null, '1');
INSERT INTO `spellextra` VALUES ('20817', null, null, '1');
INSERT INTO `spellextra` VALUES ('22189', null, null, '1');
INSERT INTO `spellextra` VALUES ('22936', null, null, '1');
INSERT INTO `spellextra` VALUES ('22947', null, null, '1');
INSERT INTO `spellextra` VALUES ('25379', null, null, '1');
INSERT INTO `spellextra` VALUES ('25380', null, null, '1');
INSERT INTO `spellextra` VALUES ('25779', null, null, '1');
INSERT INTO `spellextra` VALUES ('26046', null, null, '1');
INSERT INTO `spellextra` VALUES ('26049', null, null, '1');
INSERT INTO `spellextra` VALUES ('27992', null, null, '1');
INSERT INTO `spellextra` VALUES ('28301', null, null, '1');
INSERT INTO `spellextra` VALUES ('29310', null, null, '1');
INSERT INTO `spellextra` VALUES ('29405', null, null, '1');
INSERT INTO `spellextra` VALUES ('31729', null, null, '1');
INSERT INTO `spellextra` VALUES ('33385', null, null, '1');
INSERT INTO `spellextra` VALUES ('34930', null, null, '1');
INSERT INTO `spellextra` VALUES ('34931', null, null, '1');
INSERT INTO `spellextra` VALUES ('36484', null, null, '1');
INSERT INTO `spellextra` VALUES ('37159', null, null, '1');
INSERT INTO `spellextra` VALUES ('37176', null, null, '1');
INSERT INTO `spellextra` VALUES ('38883', null, null, '1');
INSERT INTO `spellextra` VALUES ('38884', null, null, '1');
INSERT INTO `spellextra` VALUES ('39020', null, null, '1');
INSERT INTO `spellextra` VALUES ('39136', null, null, '1');
INSERT INTO `spellextra` VALUES ('39262', null, null, '1');
INSERT INTO `spellextra` VALUES ('9484', null, null, '1');
INSERT INTO `spellextra` VALUES ('9485', null, null, '1');
INSERT INTO `spellextra` VALUES ('10955', null, null, '1');
INSERT INTO `spellextra` VALUES ('11444', null, null, '1');
INSERT INTO `spellextra` VALUES ('18137', null, null, '1');
INSERT INTO `spellextra` VALUES ('19308', null, null, '1');
INSERT INTO `spellextra` VALUES ('19309', null, null, '1');
INSERT INTO `spellextra` VALUES ('19310', null, null, '1');
INSERT INTO `spellextra` VALUES ('19311', null, null, '1');
INSERT INTO `spellextra` VALUES ('19312', null, null, '1');
INSERT INTO `spellextra` VALUES ('25477', null, null, '1');
INSERT INTO `spellextra` VALUES ('28376', null, null, '1');
INSERT INTO `spellextra` VALUES ('28377', null, null, '1');
INSERT INTO `spellextra` VALUES ('28378', null, null, '1');
INSERT INTO `spellextra` VALUES ('28379', null, null, '1');
INSERT INTO `spellextra` VALUES ('28380', null, null, '1');
INSERT INTO `spellextra` VALUES ('28381', null, null, '1');
INSERT INTO `spellextra` VALUES ('28382', null, null, '1');
INSERT INTO `spellextra` VALUES ('28385', null, null, '1');
INSERT INTO `spellextra` VALUES ('32861', null, null, '1');
INSERT INTO `spellextra` VALUES ('38379', null, null, '1');
INSERT INTO `spellextra` VALUES ('2944', null, null, '1');
INSERT INTO `spellextra` VALUES ('19276', null, null, '1');
INSERT INTO `spellextra` VALUES ('19277', null, null, '1');
INSERT INTO `spellextra` VALUES ('19278', null, null, '1');
INSERT INTO `spellextra` VALUES ('19279', null, null, '1');
INSERT INTO `spellextra` VALUES ('19280', null, null, '1');
INSERT INTO `spellextra` VALUES ('25467', null, null, '1');
INSERT INTO `spellextra` VALUES ('15407', null, null, '1');
INSERT INTO `spellextra` VALUES ('16568', null, null, '1');
INSERT INTO `spellextra` VALUES ('17165', null, null, '1');
INSERT INTO `spellextra` VALUES ('17311', null, null, '1');
INSERT INTO `spellextra` VALUES ('17312', null, null, '1');
INSERT INTO `spellextra` VALUES ('17313', null, null, '1');
INSERT INTO `spellextra` VALUES ('17314', null, null, '1');
INSERT INTO `spellextra` VALUES ('18807', null, null, '1');
INSERT INTO `spellextra` VALUES ('22919', null, null, '1');
INSERT INTO `spellextra` VALUES ('23953', null, null, '1');
INSERT INTO `spellextra` VALUES ('25387', null, null, '1');
INSERT INTO `spellextra` VALUES ('26044', null, null, '1');
INSERT INTO `spellextra` VALUES ('26143', null, null, '1');
INSERT INTO `spellextra` VALUES ('28310', null, null, '1');
INSERT INTO `spellextra` VALUES ('29407', null, null, '1');
INSERT INTO `spellextra` VALUES ('29570', null, null, '1');
INSERT INTO `spellextra` VALUES ('32417', null, null, '1');
INSERT INTO `spellextra` VALUES ('35507', null, null, '1');
INSERT INTO `spellextra` VALUES ('37276', null, null, '1');
INSERT INTO `spellextra` VALUES ('37330', null, null, '1');
INSERT INTO `spellextra` VALUES ('37621', null, null, '1');
INSERT INTO `spellextra` VALUES ('38243', null, null, '1');
INSERT INTO `spellextra` VALUES ('14914', null, null, '1');
INSERT INTO `spellextra` VALUES ('15261', null, null, '1');
INSERT INTO `spellextra` VALUES ('15262', null, null, '1');
INSERT INTO `spellextra` VALUES ('15263', null, null, '1');
INSERT INTO `spellextra` VALUES ('15264', null, null, '1');
INSERT INTO `spellextra` VALUES ('15265', null, null, '1');
INSERT INTO `spellextra` VALUES ('15266', null, null, '1');
INSERT INTO `spellextra` VALUES ('15267', null, null, '1');
INSERT INTO `spellextra` VALUES ('17140', null, null, '1');
INSERT INTO `spellextra` VALUES ('17141', null, null, '1');
INSERT INTO `spellextra` VALUES ('17142', null, null, '1');
INSERT INTO `spellextra` VALUES ('18165', null, null, '1');
INSERT INTO `spellextra` VALUES ('23860', null, null, '1');
INSERT INTO `spellextra` VALUES ('25384', null, null, '1');
INSERT INTO `spellextra` VALUES ('29522', null, null, '1');
INSERT INTO `spellextra` VALUES ('29563', null, null, '1');
INSERT INTO `spellextra` VALUES ('36947', null, null, '1');
INSERT INTO `spellextra` VALUES ('38585', null, null, '1');
INSERT INTO `spellextra` VALUES ('39323', null, null, '1');
INSERT INTO `spellextra` VALUES ('10797', null, null, '1');
INSERT INTO `spellextra` VALUES ('19296', null, null, '1');
INSERT INTO `spellextra` VALUES ('19299', null, null, '1');
INSERT INTO `spellextra` VALUES ('19302', null, null, '1');
INSERT INTO `spellextra` VALUES ('19303', null, null, '1');
INSERT INTO `spellextra` VALUES ('19304', null, null, '1');
INSERT INTO `spellextra` VALUES ('19305', null, null, '1');
INSERT INTO `spellextra` VALUES ('22822', null, null, '1');
INSERT INTO `spellextra` VALUES ('22823', null, null, '1');
INSERT INTO `spellextra` VALUES ('25446', null, null, '1');
INSERT INTO `spellextra` VALUES ('27636', null, null, '1');
INSERT INTO `spellextra` VALUES ('27765', null, null, '1');
INSERT INTO `spellextra` VALUES ('27768', null, null, '1');
INSERT INTO `spellextra` VALUES ('27769', null, null, '1');
INSERT INTO `spellextra` VALUES ('27770', null, null, '1');
INSERT INTO `spellextra` VALUES ('702', null, null, '1');
INSERT INTO `spellextra` VALUES ('1108', null, null, '1');
INSERT INTO `spellextra` VALUES ('2652', null, null, '1');
INSERT INTO `spellextra` VALUES ('2943', null, null, '1');
INSERT INTO `spellextra` VALUES ('6205', null, null, '1');
INSERT INTO `spellextra` VALUES ('7646', null, null, '1');
INSERT INTO `spellextra` VALUES ('8552', null, null, '1');
INSERT INTO `spellextra` VALUES ('9035', null, null, '1');
INSERT INTO `spellextra` VALUES ('11707', null, null, '1');
INSERT INTO `spellextra` VALUES ('11708', null, null, '1');
INSERT INTO `spellextra` VALUES ('11980', null, null, '1');
INSERT INTO `spellextra` VALUES ('12493', null, null, '1');
INSERT INTO `spellextra` VALUES ('12741', null, null, '1');
INSERT INTO `spellextra` VALUES ('17227', null, null, '1');
INSERT INTO `spellextra` VALUES ('18267', null, null, '1');
INSERT INTO `spellextra` VALUES ('19249', null, null, '1');
INSERT INTO `spellextra` VALUES ('19251', null, null, '1');
INSERT INTO `spellextra` VALUES ('19252', null, null, '1');
INSERT INTO `spellextra` VALUES ('19253', null, null, '1');
INSERT INTO `spellextra` VALUES ('19254', null, null, '1');
INSERT INTO `spellextra` VALUES ('19261', null, null, '1');
INSERT INTO `spellextra` VALUES ('19262', null, null, '1');
INSERT INTO `spellextra` VALUES ('19264', null, null, '1');
INSERT INTO `spellextra` VALUES ('19265', null, null, '1');
INSERT INTO `spellextra` VALUES ('19266', null, null, '1');
INSERT INTO `spellextra` VALUES ('19281', null, null, '1');
INSERT INTO `spellextra` VALUES ('19282', null, null, '1');
INSERT INTO `spellextra` VALUES ('19283', null, null, '1');
INSERT INTO `spellextra` VALUES ('19284', null, null, '1');
INSERT INTO `spellextra` VALUES ('19285', null, null, '1');
INSERT INTO `spellextra` VALUES ('21007', null, null, '1');
INSERT INTO `spellextra` VALUES ('25460', null, null, '1');
INSERT INTO `spellextra` VALUES ('25461', null, null, '1');
INSERT INTO `spellextra` VALUES ('25470', null, null, '1');
INSERT INTO `spellextra` VALUES ('25816', null, null, '1');
INSERT INTO `spellextra` VALUES ('27224', null, null, '1');
INSERT INTO `spellextra` VALUES ('28598', null, null, '1');
INSERT INTO `spellextra` VALUES ('30909', null, null, '1');
INSERT INTO `spellextra` VALUES ('8092', null, null, '1');
INSERT INTO `spellextra` VALUES ('8102', null, null, '1');
INSERT INTO `spellextra` VALUES ('8103', null, null, '1');
INSERT INTO `spellextra` VALUES ('8104', null, null, '1');
INSERT INTO `spellextra` VALUES ('8105', null, null, '1');
INSERT INTO `spellextra` VALUES ('8106', null, null, '1');
INSERT INTO `spellextra` VALUES ('10945', null, null, '1');
INSERT INTO `spellextra` VALUES ('10946', null, null, '1');
INSERT INTO `spellextra` VALUES ('10947', null, null, '1');
INSERT INTO `spellextra` VALUES ('13860', null, null, '1');
INSERT INTO `spellextra` VALUES ('15587', null, null, '1');
INSERT INTO `spellextra` VALUES ('17194', null, null, '1');
INSERT INTO `spellextra` VALUES ('17287', null, null, '1');
INSERT INTO `spellextra` VALUES ('20830', null, null, '1');
INSERT INTO `spellextra` VALUES ('25372', null, null, '1');
INSERT INTO `spellextra` VALUES ('25375', null, null, '1');
INSERT INTO `spellextra` VALUES ('26048', null, null, '1');
INSERT INTO `spellextra` VALUES ('31516', null, null, '1');
INSERT INTO `spellextra` VALUES ('37531', null, null, '1');
INSERT INTO `spellextra` VALUES ('38259', null, null, '1');
INSERT INTO `spellextra` VALUES ('451', null, null, '1');
INSERT INTO `spellextra` VALUES ('589', null, null, '1');
INSERT INTO `spellextra` VALUES ('593', null, null, '1');
INSERT INTO `spellextra` VALUES ('594', null, null, '1');
INSERT INTO `spellextra` VALUES ('861', null, null, '1');
INSERT INTO `spellextra` VALUES ('970', null, null, '1');
INSERT INTO `spellextra` VALUES ('992', null, null, '1');
INSERT INTO `spellextra` VALUES ('998', null, null, '1');
INSERT INTO `spellextra` VALUES ('2767', null, null, '1');
INSERT INTO `spellextra` VALUES ('5704', null, null, '1');
INSERT INTO `spellextra` VALUES ('6069', null, null, '1');
INSERT INTO `spellextra` VALUES ('10892', null, null, '1');
INSERT INTO `spellextra` VALUES ('10893', null, null, '1');
INSERT INTO `spellextra` VALUES ('10894', null, null, '1');
INSERT INTO `spellextra` VALUES ('11639', null, null, '1');
INSERT INTO `spellextra` VALUES ('14032', null, null, '1');
INSERT INTO `spellextra` VALUES ('15654', null, null, '1');
INSERT INTO `spellextra` VALUES ('17146', null, null, '1');
INSERT INTO `spellextra` VALUES ('19776', null, null, '1');
INSERT INTO `spellextra` VALUES ('23268', null, null, '1');
INSERT INTO `spellextra` VALUES ('23952', null, null, '1');
INSERT INTO `spellextra` VALUES ('24212', null, null, '1');
INSERT INTO `spellextra` VALUES ('25367', null, null, '1');
INSERT INTO `spellextra` VALUES ('25368', null, null, '1');
INSERT INTO `spellextra` VALUES ('27605', null, null, '1');
INSERT INTO `spellextra` VALUES ('30854', null, null, '1');
INSERT INTO `spellextra` VALUES ('30898', null, null, '1');
INSERT INTO `spellextra` VALUES ('32379', null, null, '1');
INSERT INTO `spellextra` VALUES ('32409', null, null, '1');
INSERT INTO `spellextra` VALUES ('32996', null, null, '1');
INSERT INTO `spellextra` VALUES ('34441', null, null, '1');
INSERT INTO `spellextra` VALUES ('34941', null, null, '1');
INSERT INTO `spellextra` VALUES ('34942', null, null, '1');
INSERT INTO `spellextra` VALUES ('37275', null, null, '1');
INSERT INTO `spellextra` VALUES ('585', null, null, '1');
INSERT INTO `spellextra` VALUES ('591', null, null, '1');
INSERT INTO `spellextra` VALUES ('598', null, null, '1');
INSERT INTO `spellextra` VALUES ('984', null, null, '1');
INSERT INTO `spellextra` VALUES ('1004', null, null, '1');
INSERT INTO `spellextra` VALUES ('6060', null, null, '1');
INSERT INTO `spellextra` VALUES ('10933', null, null, '1');
INSERT INTO `spellextra` VALUES ('10934', null, null, '1');
INSERT INTO `spellextra` VALUES ('25363', null, null, '1');
INSERT INTO `spellextra` VALUES ('25364', null, null, '1');
INSERT INTO `spellextra` VALUES ('35155', null, null, '1');
INSERT INTO `spellextra` VALUES ('31312', null, null, '1');
INSERT INTO `spellextra` VALUES ('31935', null, null, '1');
INSERT INTO `spellextra` VALUES ('32674', null, null, '1');
INSERT INTO `spellextra` VALUES ('32699', null, null, '1');
INSERT INTO `spellextra` VALUES ('32700', null, null, '1');
INSERT INTO `spellextra` VALUES ('32774', null, null, '1');
INSERT INTO `spellextra` VALUES ('37554', null, null, '1');
INSERT INTO `spellextra` VALUES ('38631', null, null, '1');
INSERT INTO `spellextra` VALUES ('24239', null, null, '1');
INSERT INTO `spellextra` VALUES ('24274', null, null, '1');
INSERT INTO `spellextra` VALUES ('24275', null, null, '1');
INSERT INTO `spellextra` VALUES ('27180', null, null, '1');
INSERT INTO `spellextra` VALUES ('32772', null, null, '1');
INSERT INTO `spellextra` VALUES ('37251', null, null, '1');
INSERT INTO `spellextra` VALUES ('37255', null, null, '1');
INSERT INTO `spellextra` VALUES ('37259', null, null, '1');
INSERT INTO `spellextra` VALUES ('20473', null, null, '1');
INSERT INTO `spellextra` VALUES ('20929', null, null, '1');
INSERT INTO `spellextra` VALUES ('20930', null, null, '1');
INSERT INTO `spellextra` VALUES ('25902', null, null, '1');
INSERT INTO `spellextra` VALUES ('25903', null, null, '1');
INSERT INTO `spellextra` VALUES ('25911', null, null, '1');
INSERT INTO `spellextra` VALUES ('25912', null, null, '1');
INSERT INTO `spellextra` VALUES ('25913', null, null, '1');
INSERT INTO `spellextra` VALUES ('25914', null, null, '1');
INSERT INTO `spellextra` VALUES ('27174', null, null, '1');
INSERT INTO `spellextra` VALUES ('27175', null, null, '1');
INSERT INTO `spellextra` VALUES ('27176', null, null, '1');
INSERT INTO `spellextra` VALUES ('32771', null, null, '1');
INSERT INTO `spellextra` VALUES ('33072', null, null, '1');
INSERT INTO `spellextra` VALUES ('33073', null, null, '1');
INSERT INTO `spellextra` VALUES ('33074', null, null, '1');
INSERT INTO `spellextra` VALUES ('35160', null, null, '1');
INSERT INTO `spellextra` VALUES ('36340', null, null, '1');
INSERT INTO `spellextra` VALUES ('38921', null, null, '1');
INSERT INTO `spellextra` VALUES ('879', null, null, '1');
INSERT INTO `spellextra` VALUES ('5614', null, null, '1');
INSERT INTO `spellextra` VALUES ('5615', null, null, '1');
INSERT INTO `spellextra` VALUES ('10312', null, null, '1');
INSERT INTO `spellextra` VALUES ('10313', null, null, '1');
INSERT INTO `spellextra` VALUES ('10314', null, null, '1');
INSERT INTO `spellextra` VALUES ('17147', null, null, '1');
INSERT INTO `spellextra` VALUES ('17149', null, null, '1');
INSERT INTO `spellextra` VALUES ('27138', null, null, '1');
INSERT INTO `spellextra` VALUES ('33632', null, null, '1');
INSERT INTO `spellextra` VALUES ('853', null, null, '1');
INSERT INTO `spellextra` VALUES ('5588', null, null, '1');
INSERT INTO `spellextra` VALUES ('5589', null, null, '1');
INSERT INTO `spellextra` VALUES ('10308', null, null, '1');
INSERT INTO `spellextra` VALUES ('13005', null, null, '1');
INSERT INTO `spellextra` VALUES ('32416', null, null, '1');
INSERT INTO `spellextra` VALUES ('37369', null, null, '1');
INSERT INTO `spellextra` VALUES ('39077', null, null, '1');
INSERT INTO `spellextra` VALUES ('3674', null, null, '1');
INSERT INTO `spellextra` VALUES ('14296', null, null, '1');
INSERT INTO `spellextra` VALUES ('20733', null, null, '1');
INSERT INTO `spellextra` VALUES ('1510', null, null, '1');
INSERT INTO `spellextra` VALUES ('1540', null, null, '1');
INSERT INTO `spellextra` VALUES ('3013', null, null, '1');
INSERT INTO `spellextra` VALUES ('14294', null, null, '1');
INSERT INTO `spellextra` VALUES ('14295', null, null, '1');
INSERT INTO `spellextra` VALUES ('22908', null, null, '1');
INSERT INTO `spellextra` VALUES ('27022', null, null, '1');
INSERT INTO `spellextra` VALUES ('30933', null, null, '1');
INSERT INTO `spellextra` VALUES ('34100', null, null, '1');
INSERT INTO `spellextra` VALUES ('35950', null, null, '1');
INSERT INTO `spellextra` VALUES ('19386', null, null, '1');
INSERT INTO `spellextra` VALUES ('24131', null, null, '1');
INSERT INTO `spellextra` VALUES ('24132', null, null, '1');
INSERT INTO `spellextra` VALUES ('24133', null, null, '1');
INSERT INTO `spellextra` VALUES ('24134', null, null, '1');
INSERT INTO `spellextra` VALUES ('24135', null, null, '1');
INSERT INTO `spellextra` VALUES ('24335', null, null, '1');
INSERT INTO `spellextra` VALUES ('24336', null, null, '1');
INSERT INTO `spellextra` VALUES ('26180', null, null, '1');
INSERT INTO `spellextra` VALUES ('26233', null, null, '1');
INSERT INTO `spellextra` VALUES ('26748', null, null, '1');
INSERT INTO `spellextra` VALUES ('27068', null, null, '1');
INSERT INTO `spellextra` VALUES ('27069', null, null, '1');
INSERT INTO `spellextra` VALUES ('3034', null, null, '1');
INSERT INTO `spellextra` VALUES ('14279', null, null, '1');
INSERT INTO `spellextra` VALUES ('14280', null, null, '1');
INSERT INTO `spellextra` VALUES ('27018', null, null, '1');
INSERT INTO `spellextra` VALUES ('31407', null, null, '1');
INSERT INTO `spellextra` VALUES ('37551', null, null, '1');
INSERT INTO `spellextra` VALUES ('39413', null, null, '1');
INSERT INTO `spellextra` VALUES ('19306', null, null, '1');
INSERT INTO `spellextra` VALUES ('20909', null, null, '1');
INSERT INTO `spellextra` VALUES ('20910', null, null, '1');
INSERT INTO `spellextra` VALUES ('27067', null, null, '1');
INSERT INTO `spellextra` VALUES ('2643', null, null, '1');
INSERT INTO `spellextra` VALUES ('14288', null, null, '1');
INSERT INTO `spellextra` VALUES ('14289', null, null, '1');
INSERT INTO `spellextra` VALUES ('14290', null, null, '1');
INSERT INTO `spellextra` VALUES ('14443', null, null, '1');
INSERT INTO `spellextra` VALUES ('18651', null, null, '1');
INSERT INTO `spellextra` VALUES ('20735', null, null, '1');
INSERT INTO `spellextra` VALUES ('21390', null, null, '1');
INSERT INTO `spellextra` VALUES ('25294', null, null, '1');
INSERT INTO `spellextra` VALUES ('27021', null, null, '1');
INSERT INTO `spellextra` VALUES ('29576', null, null, '1');
INSERT INTO `spellextra` VALUES ('30990', null, null, '1');
INSERT INTO `spellextra` VALUES ('31942', null, null, '1');
INSERT INTO `spellextra` VALUES ('34879', null, null, '1');
INSERT INTO `spellextra` VALUES ('34974', null, null, '1');
INSERT INTO `spellextra` VALUES ('36979', null, null, '1');
INSERT INTO `spellextra` VALUES ('37790', null, null, '1');
INSERT INTO `spellextra` VALUES ('38310', null, null, '1');
INSERT INTO `spellextra` VALUES ('38383', null, null, '1');
INSERT INTO `spellextra` VALUES ('1495', null, null, '1');
INSERT INTO `spellextra` VALUES ('14269', null, null, '1');
INSERT INTO `spellextra` VALUES ('14270', null, null, '1');
INSERT INTO `spellextra` VALUES ('14271', null, null, '1');
INSERT INTO `spellextra` VALUES ('36916', null, null, '1');
INSERT INTO `spellextra` VALUES ('2974', null, null, '1');
INSERT INTO `spellextra` VALUES ('14267', null, null, '1');
INSERT INTO `spellextra` VALUES ('14268', null, null, '1');
INSERT INTO `spellextra` VALUES ('19229', null, null, '1');
INSERT INTO `spellextra` VALUES ('27633', null, null, '1');
INSERT INTO `spellextra` VALUES ('32908', null, null, '1');
INSERT INTO `spellextra` VALUES ('35963', null, null, '1');
INSERT INTO `spellextra` VALUES ('3044', null, null, '1');
INSERT INTO `spellextra` VALUES ('14281', null, null, '1');
INSERT INTO `spellextra` VALUES ('14282', null, null, '1');
INSERT INTO `spellextra` VALUES ('14283', null, null, '1');
INSERT INTO `spellextra` VALUES ('14284', null, null, '1');
INSERT INTO `spellextra` VALUES ('14285', null, null, '1');
INSERT INTO `spellextra` VALUES ('14286', null, null, '1');
INSERT INTO `spellextra` VALUES ('14287', null, null, '1');
INSERT INTO `spellextra` VALUES ('27019', null, null, '1');
INSERT INTO `spellextra` VALUES ('34829', null, null, '1');
INSERT INTO `spellextra` VALUES ('35401', null, null, '1');
INSERT INTO `spellextra` VALUES ('36293', null, null, '1');
INSERT INTO `spellextra` VALUES ('36608', null, null, '1');
INSERT INTO `spellextra` VALUES ('36609', null, null, '1');
INSERT INTO `spellextra` VALUES ('36623', null, null, '1');
INSERT INTO `spellextra` VALUES ('38807', null, null, '1');
INSERT INTO `spellextra` VALUES ('38808', null, null, '1');
INSERT INTO `spellextra` VALUES ('1130', null, null, '1');
INSERT INTO `spellextra` VALUES ('14323', null, null, '1');
INSERT INTO `spellextra` VALUES ('14324', null, null, '1');
INSERT INTO `spellextra` VALUES ('14325', null, null, '1');
INSERT INTO `spellextra` VALUES ('31615', null, null, '1');
INSERT INTO `spellextra` VALUES ('34832', null, null, '1');
INSERT INTO `spellextra` VALUES ('13553', null, null, '1');
INSERT INTO `spellextra` VALUES ('13554', null, null, '1');
INSERT INTO `spellextra` VALUES ('13555', null, null, '1');
INSERT INTO `spellextra` VALUES ('25295', null, null, '1');
INSERT INTO `spellextra` VALUES ('27016', null, null, '1');
INSERT INTO `spellextra` VALUES ('31975', null, null, '1');
INSERT INTO `spellextra` VALUES ('35511', null, null, '1');
INSERT INTO `spellextra` VALUES ('36984', null, null, '1');
INSERT INTO `spellextra` VALUES ('38859', null, null, '1');
INSERT INTO `spellextra` VALUES ('38914', null, null, '1');
INSERT INTO `spellextra` VALUES ('39182', null, null, '1');
INSERT INTO `spellextra` VALUES ('3720', null, null, '1');
INSERT INTO `spellextra` VALUES ('3823', null, null, '1');
INSERT INTO `spellextra` VALUES ('4164', null, null, '1');
INSERT INTO `spellextra` VALUES ('4165', null, null, '1');
INSERT INTO `spellextra` VALUES ('7978', null, null, '1');
INSERT INTO `spellextra` VALUES ('10277', null, null, '1');
INSERT INTO `spellextra` VALUES ('13398', null, null, '1');
INSERT INTO `spellextra` VALUES ('15607', null, null, '1');
INSERT INTO `spellextra` VALUES ('15619', null, null, '1');
INSERT INTO `spellextra` VALUES ('15795', null, null, '1');
INSERT INTO `spellextra` VALUES ('16000', null, null, '1');
INSERT INTO `spellextra` VALUES ('16075', null, null, '1');
INSERT INTO `spellextra` VALUES ('19032', null, null, '1');
INSERT INTO `spellextra` VALUES ('19785', null, null, '1');
INSERT INTO `spellextra` VALUES ('22887', null, null, '1');
INSERT INTO `spellextra` VALUES ('23968', null, null, '1');
INSERT INTO `spellextra` VALUES ('23969', null, null, '1');
INSERT INTO `spellextra` VALUES ('23970', null, null, '1');
INSERT INTO `spellextra` VALUES ('25004', null, null, '1');
INSERT INTO `spellextra` VALUES ('27662', null, null, '1');
INSERT INTO `spellextra` VALUES ('29579', null, null, '1');
INSERT INTO `spellextra` VALUES ('29582', null, null, '1');
INSERT INTO `spellextra` VALUES ('30846', null, null, '1');
INSERT INTO `spellextra` VALUES ('31946', null, null, '1');
INSERT INTO `spellextra` VALUES ('32001', null, null, '1');
INSERT INTO `spellextra` VALUES ('32784', null, null, '1');
INSERT INTO `spellextra` VALUES ('33670', null, null, '1');
INSERT INTO `spellextra` VALUES ('33805', null, null, '1');
INSERT INTO `spellextra` VALUES ('33806', null, null, '1');
INSERT INTO `spellextra` VALUES ('33822', null, null, '1');
INSERT INTO `spellextra` VALUES ('34095', null, null, '1');
INSERT INTO `spellextra` VALUES ('34389', null, null, '1');
INSERT INTO `spellextra` VALUES ('35139', null, null, '1');
INSERT INTO `spellextra` VALUES ('35276', null, null, '1');
INSERT INTO `spellextra` VALUES ('35724', null, null, '1');
INSERT INTO `spellextra` VALUES ('36645', null, null, '1');
INSERT INTO `spellextra` VALUES ('36651', null, null, '1');
INSERT INTO `spellextra` VALUES ('38556', null, null, '1');
INSERT INTO `spellextra` VALUES ('38557', null, null, '1');
INSERT INTO `spellextra` VALUES ('38558', null, null, '1');
INSERT INTO `spellextra` VALUES ('38559', null, null, '1');
INSERT INTO `spellextra` VALUES ('38560', null, null, '1');
INSERT INTO `spellextra` VALUES ('38561', null, null, '1');
INSERT INTO `spellextra` VALUES ('38562', null, null, '1');
INSERT INTO `spellextra` VALUES ('38563', null, null, '1');
INSERT INTO `spellextra` VALUES ('38564', null, null, '1');
INSERT INTO `spellextra` VALUES ('38565', null, null, '1');
INSERT INTO `spellextra` VALUES ('38566', null, null, '1');
INSERT INTO `spellextra` VALUES ('38567', null, null, '1');
INSERT INTO `spellextra` VALUES ('38568', null, null, '1');
INSERT INTO `spellextra` VALUES ('38569', null, null, '1');
INSERT INTO `spellextra` VALUES ('38570', null, null, '1');
INSERT INTO `spellextra` VALUES ('38904', null, null, '1');
INSERT INTO `spellextra` VALUES ('39060', null, null, '1');
INSERT INTO `spellextra` VALUES ('39146', null, null, '1');
INSERT INTO `spellextra` VALUES ('39147', null, null, '1');
INSERT INTO `spellextra` VALUES ('39148', null, null, '1');
INSERT INTO `spellextra` VALUES ('39149', null, null, '1');
INSERT INTO `spellextra` VALUES ('39150', null, null, '1');
INSERT INTO `spellextra` VALUES ('39151', null, null, '1');
INSERT INTO `spellextra` VALUES ('39154', null, null, '1');
INSERT INTO `spellextra` VALUES ('39155', null, null, '1');
INSERT INTO `spellextra` VALUES ('39156', null, null, '1');
INSERT INTO `spellextra` VALUES ('75', null, null, '1');
INSERT INTO `spellextra` VALUES ('2973', null, null, '1');
INSERT INTO `spellextra` VALUES ('14260', null, null, '1');
INSERT INTO `spellextra` VALUES ('14261', null, null, '1');
INSERT INTO `spellextra` VALUES ('14262', null, null, '1');
INSERT INTO `spellextra` VALUES ('14263', null, null, '1');
INSERT INTO `spellextra` VALUES ('14264', null, null, '1');
INSERT INTO `spellextra` VALUES ('14265', null, null, '1');
INSERT INTO `spellextra` VALUES ('14266', null, null, '1');
INSERT INTO `spellextra` VALUES ('27014', null, null, '1');
INSERT INTO `spellextra` VALUES ('31566', null, null, '1');
INSERT INTO `spellextra` VALUES ('32915', null, null, '1');
INSERT INTO `spellextra` VALUES ('5422', null, null, '1');
INSERT INTO `spellextra` VALUES ('33745', null, null, '1');
INSERT INTO `spellextra` VALUES ('27243', null, null, '1');
INSERT INTO `spellextra` VALUES ('27285', null, null, '1');
INSERT INTO `spellextra` VALUES ('32863', null, null, '1');
INSERT INTO `spellextra` VALUES ('32865', null, null, '1');
INSERT INTO `spellextra` VALUES ('36123', null, null, '1');
INSERT INTO `spellextra` VALUES ('37826', null, null, '1');
INSERT INTO `spellextra` VALUES ('38252', null, null, '1');
INSERT INTO `spellextra` VALUES ('39367', null, null, '1');
INSERT INTO `spellextra` VALUES ('19397', null, null, '1');
INSERT INTO `spellextra` VALUES ('23308', null, null, '1');
INSERT INTO `spellextra` VALUES ('23309', null, null, '1');
INSERT INTO `spellextra` VALUES ('29722', null, null, '1');
INSERT INTO `spellextra` VALUES ('32231', null, null, '1');
INSERT INTO `spellextra` VALUES ('32707', null, null, '1');
INSERT INTO `spellextra` VALUES ('36832', null, null, '1');
INSERT INTO `spellextra` VALUES ('38401', null, null, '1');
INSERT INTO `spellextra` VALUES ('38918', null, null, '1');
INSERT INTO `spellextra` VALUES ('39083', null, null, '1');
INSERT INTO `spellextra` VALUES ('603', null, null, '1');
INSERT INTO `spellextra` VALUES ('18662', null, null, '1');
INSERT INTO `spellextra` VALUES ('18734', null, null, '1');
INSERT INTO `spellextra` VALUES ('30910', null, null, '1');
INSERT INTO `spellextra` VALUES ('30108', null, null, '1');
INSERT INTO `spellextra` VALUES ('30404', null, null, '1');
INSERT INTO `spellextra` VALUES ('30405', null, null, '1');
INSERT INTO `spellextra` VALUES ('31117', null, null, '1');
INSERT INTO `spellextra` VALUES ('34438', null, null, '1');
INSERT INTO `spellextra` VALUES ('34439', null, null, '1');
INSERT INTO `spellextra` VALUES ('35183', null, null, '1');
INSERT INTO `spellextra` VALUES ('6353', null, null, '1');
INSERT INTO `spellextra` VALUES ('17924', null, null, '1');
INSERT INTO `spellextra` VALUES ('27211', null, null, '1');
INSERT INTO `spellextra` VALUES ('30545', null, null, '1');
INSERT INTO `spellextra` VALUES ('17862', null, null, '1');
INSERT INTO `spellextra` VALUES ('17937', null, null, '1');
INSERT INTO `spellextra` VALUES ('27229', null, null, '1');
INSERT INTO `spellextra` VALUES ('6789', null, null, '1');
INSERT INTO `spellextra` VALUES ('17925', null, null, '1');
INSERT INTO `spellextra` VALUES ('17926', null, null, '1');
INSERT INTO `spellextra` VALUES ('27223', null, null, '1');
INSERT INTO `spellextra` VALUES ('28412', null, null, '1');
INSERT INTO `spellextra` VALUES ('30500', null, null, '1');
INSERT INTO `spellextra` VALUES ('30741', null, null, '1');
INSERT INTO `spellextra` VALUES ('32709', null, null, '1');
INSERT INTO `spellextra` VALUES ('33130', null, null, '1');
INSERT INTO `spellextra` VALUES ('34437', null, null, '1');
INSERT INTO `spellextra` VALUES ('35954', null, null, '1');
INSERT INTO `spellextra` VALUES ('38065', null, null, '1');
INSERT INTO `spellextra` VALUES ('1010', null, null, '1');
INSERT INTO `spellextra` VALUES ('1490', null, null, '1');
INSERT INTO `spellextra` VALUES ('11721', null, null, '1');
INSERT INTO `spellextra` VALUES ('11722', null, null, '1');
INSERT INTO `spellextra` VALUES ('27228', null, null, '1');
INSERT INTO `spellextra` VALUES ('36831', null, null, '1');
INSERT INTO `spellextra` VALUES ('711', null, null, '1');
INSERT INTO `spellextra` VALUES ('1949', null, null, '1');
INSERT INTO `spellextra` VALUES ('11683', null, null, '1');
INSERT INTO `spellextra` VALUES ('11684', null, null, '1');
INSERT INTO `spellextra` VALUES ('27213', null, null, '1');
INSERT INTO `spellextra` VALUES ('30859', null, null, '1');
INSERT INTO `spellextra` VALUES ('34659', null, null, '1');
INSERT INTO `spellextra` VALUES ('34660', null, null, '1');
INSERT INTO `spellextra` VALUES ('37428', null, null, '1');
INSERT INTO `spellextra` VALUES ('39131', null, null, '1');
INSERT INTO `spellextra` VALUES ('39132', null, null, '1');
INSERT INTO `spellextra` VALUES ('18265', null, null, '1');
INSERT INTO `spellextra` VALUES ('18879', null, null, '1');
INSERT INTO `spellextra` VALUES ('18880', null, null, '1');
INSERT INTO `spellextra` VALUES ('18881', null, null, '1');
INSERT INTO `spellextra` VALUES ('27264', null, null, '1');
INSERT INTO `spellextra` VALUES ('30911', null, null, '1');
INSERT INTO `spellextra` VALUES ('35195', null, null, '1');
INSERT INTO `spellextra` VALUES ('1098', null, null, '1');
INSERT INTO `spellextra` VALUES ('11725', null, null, '1');
INSERT INTO `spellextra` VALUES ('11726', null, null, '1');
INSERT INTO `spellextra` VALUES ('20882', null, null, '1');
INSERT INTO `spellextra` VALUES ('710', null, null, '1');
INSERT INTO `spellextra` VALUES ('8994', null, null, '1');
INSERT INTO `spellextra` VALUES ('18647', null, null, '1');
INSERT INTO `spellextra` VALUES ('24466', null, null, '1');
INSERT INTO `spellextra` VALUES ('27565', null, null, '1');
INSERT INTO `spellextra` VALUES ('30231', null, null, '1');
INSERT INTO `spellextra` VALUES ('35182', null, null, '1');
INSERT INTO `spellextra` VALUES ('37527', null, null, '1');
INSERT INTO `spellextra` VALUES ('37546', null, null, '1');
INSERT INTO `spellextra` VALUES ('37833', null, null, '1');
INSERT INTO `spellextra` VALUES ('38009', null, null, '1');
INSERT INTO `spellextra` VALUES ('38376', null, null, '1');
INSERT INTO `spellextra` VALUES ('38791', null, null, '1');
INSERT INTO `spellextra` VALUES ('1714', null, null, '1');
INSERT INTO `spellextra` VALUES ('11719', null, null, '1');
INSERT INTO `spellextra` VALUES ('12889', null, null, '1');
INSERT INTO `spellextra` VALUES ('13338', null, null, '1');
INSERT INTO `spellextra` VALUES ('15470', null, null, '1');
INSERT INTO `spellextra` VALUES ('25195', null, null, '1');
INSERT INTO `spellextra` VALUES ('5138', null, null, '1');
INSERT INTO `spellextra` VALUES ('6226', null, null, '1');
INSERT INTO `spellextra` VALUES ('11703', null, null, '1');
INSERT INTO `spellextra` VALUES ('11704', null, null, '1');
INSERT INTO `spellextra` VALUES ('17008', null, null, '1');
INSERT INTO `spellextra` VALUES ('17243', null, null, '1');
INSERT INTO `spellextra` VALUES ('17682', null, null, '1');
INSERT INTO `spellextra` VALUES ('25671', null, null, '1');
INSERT INTO `spellextra` VALUES ('25676', null, null, '1');
INSERT INTO `spellextra` VALUES ('25754', null, null, '1');
INSERT INTO `spellextra` VALUES ('25755', null, null, '1');
INSERT INTO `spellextra` VALUES ('26457', null, null, '1');
INSERT INTO `spellextra` VALUES ('26559', null, null, '1');
INSERT INTO `spellextra` VALUES ('26639', null, null, '1');
INSERT INTO `spellextra` VALUES ('27221', null, null, '1');
INSERT INTO `spellextra` VALUES ('29058', null, null, '1');
INSERT INTO `spellextra` VALUES ('29881', null, null, '1');
INSERT INTO `spellextra` VALUES ('30908', null, null, '1');
INSERT INTO `spellextra` VALUES ('32554', null, null, '1');
INSERT INTO `spellextra` VALUES ('34806', null, null, '1');
INSERT INTO `spellextra` VALUES ('35332', null, null, '1');
INSERT INTO `spellextra` VALUES ('36088', null, null, '1');
INSERT INTO `spellextra` VALUES ('36095', null, null, '1');
INSERT INTO `spellextra` VALUES ('26385', null, null, '1');
INSERT INTO `spellextra` VALUES ('29341', null, null, '1');
INSERT INTO `spellextra` VALUES ('5676', null, null, '1');
INSERT INTO `spellextra` VALUES ('17919', null, null, '1');
INSERT INTO `spellextra` VALUES ('17920', null, null, '1');
INSERT INTO `spellextra` VALUES ('17921', null, null, '1');
INSERT INTO `spellextra` VALUES ('17922', null, null, '1');
INSERT INTO `spellextra` VALUES ('17923', null, null, '1');
INSERT INTO `spellextra` VALUES ('27210', null, null, '1');
INSERT INTO `spellextra` VALUES ('29492', null, null, '1');
INSERT INTO `spellextra` VALUES ('30358', null, null, '1');
INSERT INTO `spellextra` VALUES ('30459', null, null, '1');
INSERT INTO `spellextra` VALUES ('689', null, null, '1');
INSERT INTO `spellextra` VALUES ('699', null, null, '1');
INSERT INTO `spellextra` VALUES ('709', null, null, '1');
INSERT INTO `spellextra` VALUES ('7651', null, null, '1');
INSERT INTO `spellextra` VALUES ('11699', null, null, '1');
INSERT INTO `spellextra` VALUES ('11700', null, null, '1');
INSERT INTO `spellextra` VALUES ('12693', null, null, '1');
INSERT INTO `spellextra` VALUES ('16375', null, null, '1');
INSERT INTO `spellextra` VALUES ('16414', null, null, '1');
INSERT INTO `spellextra` VALUES ('16608', null, null, '1');
INSERT INTO `spellextra` VALUES ('17173', null, null, '1');
INSERT INTO `spellextra` VALUES ('17238', null, null, '1');
INSERT INTO `spellextra` VALUES ('17620', null, null, '1');
INSERT INTO `spellextra` VALUES ('18084', null, null, '1');
INSERT INTO `spellextra` VALUES ('18557', null, null, '1');
INSERT INTO `spellextra` VALUES ('18817', null, null, '1');
INSERT INTO `spellextra` VALUES ('20743', null, null, '1');
INSERT INTO `spellextra` VALUES ('21170', null, null, '1');
INSERT INTO `spellextra` VALUES ('24300', null, null, '1');
INSERT INTO `spellextra` VALUES ('24435', null, null, '1');
INSERT INTO `spellextra` VALUES ('24585', null, null, '1');
INSERT INTO `spellextra` VALUES ('24618', null, null, '1');
INSERT INTO `spellextra` VALUES ('26693', null, null, '1');
INSERT INTO `spellextra` VALUES ('27219', null, null, '1');
INSERT INTO `spellextra` VALUES ('27220', null, null, '1');
INSERT INTO `spellextra` VALUES ('27994', null, null, '1');
INSERT INTO `spellextra` VALUES ('29155', null, null, '1');
INSERT INTO `spellextra` VALUES ('30412', null, null, '1');
INSERT INTO `spellextra` VALUES ('34107', null, null, '1');
INSERT INTO `spellextra` VALUES ('34696', null, null, '1');
INSERT INTO `spellextra` VALUES ('35748', null, null, '1');
INSERT INTO `spellextra` VALUES ('36224', null, null, '1');
INSERT INTO `spellextra` VALUES ('36655', null, null, '1');
INSERT INTO `spellextra` VALUES ('36825', null, null, '1');
INSERT INTO `spellextra` VALUES ('37992', null, null, '1');
INSERT INTO `spellextra` VALUES ('38817', null, null, '1');
INSERT INTO `spellextra` VALUES ('704', null, null, '1');
INSERT INTO `spellextra` VALUES ('7658', null, null, '1');
INSERT INTO `spellextra` VALUES ('7659', null, null, '1');
INSERT INTO `spellextra` VALUES ('11717', null, null, '1');
INSERT INTO `spellextra` VALUES ('16231', null, null, '1');
INSERT INTO `spellextra` VALUES ('27226', null, null, '1');
INSERT INTO `spellextra` VALUES ('1120', null, null, '1');
INSERT INTO `spellextra` VALUES ('8288', null, null, '1');
INSERT INTO `spellextra` VALUES ('8289', null, null, '1');
INSERT INTO `spellextra` VALUES ('11675', null, null, '1');
INSERT INTO `spellextra` VALUES ('18371', null, null, '1');
INSERT INTO `spellextra` VALUES ('27217', null, null, '1');
INSERT INTO `spellextra` VALUES ('32862', null, null, '1');
INSERT INTO `spellextra` VALUES ('35839', null, null, '1');
INSERT INTO `spellextra` VALUES ('16', null, null, '1');
INSERT INTO `spellextra` VALUES ('830', null, null, '1');
INSERT INTO `spellextra` VALUES ('5782', null, null, '1');
INSERT INTO `spellextra` VALUES ('6213', null, null, '1');
INSERT INTO `spellextra` VALUES ('6215', null, null, '1');
INSERT INTO `spellextra` VALUES ('6346', null, null, '1');
INSERT INTO `spellextra` VALUES ('12096', null, null, '1');
INSERT INTO `spellextra` VALUES ('12542', null, null, '1');
INSERT INTO `spellextra` VALUES ('12733', null, null, '1');
INSERT INTO `spellextra` VALUES ('22678', null, null, '1');
INSERT INTO `spellextra` VALUES ('26070', null, null, '1');
INSERT INTO `spellextra` VALUES ('26580', null, null, '1');
INSERT INTO `spellextra` VALUES ('26661', null, null, '1');
INSERT INTO `spellextra` VALUES ('27641', null, null, '1');
INSERT INTO `spellextra` VALUES ('27990', null, null, '1');
INSERT INTO `spellextra` VALUES ('29168', null, null, '1');
INSERT INTO `spellextra` VALUES ('29321', null, null, '1');
INSERT INTO `spellextra` VALUES ('30002', null, null, '1');
INSERT INTO `spellextra` VALUES ('30530', null, null, '1');
INSERT INTO `spellextra` VALUES ('30584', null, null, '1');
INSERT INTO `spellextra` VALUES ('30615', null, null, '1');
INSERT INTO `spellextra` VALUES ('31358', null, null, '1');
INSERT INTO `spellextra` VALUES ('31970', null, null, '1');
INSERT INTO `spellextra` VALUES ('32241', null, null, '1');
INSERT INTO `spellextra` VALUES ('33547', null, null, '1');
INSERT INTO `spellextra` VALUES ('33629', null, null, '1');
INSERT INTO `spellextra` VALUES ('33924', null, null, '1');
INSERT INTO `spellextra` VALUES ('34076', null, null, '1');
INSERT INTO `spellextra` VALUES ('34259', null, null, '1');
INSERT INTO `spellextra` VALUES ('38154', null, null, '1');
INSERT INTO `spellextra` VALUES ('38595', null, null, '1');
INSERT INTO `spellextra` VALUES ('38660', null, null, '1');
INSERT INTO `spellextra` VALUES ('39119', null, null, '1');
INSERT INTO `spellextra` VALUES ('39176', null, null, '1');
INSERT INTO `spellextra` VALUES ('39210', null, null, '1');
INSERT INTO `spellextra` VALUES ('39415', null, null, '1');
INSERT INTO `spellextra` VALUES ('980', null, null, '1');
INSERT INTO `spellextra` VALUES ('1014', null, null, '1');
INSERT INTO `spellextra` VALUES ('6217', null, null, '1');
INSERT INTO `spellextra` VALUES ('11711', null, null, '1');
INSERT INTO `spellextra` VALUES ('11712', null, null, '1');
INSERT INTO `spellextra` VALUES ('11713', null, null, '1');
INSERT INTO `spellextra` VALUES ('14868', null, null, '1');
INSERT INTO `spellextra` VALUES ('14875', null, null, '1');
INSERT INTO `spellextra` VALUES ('17771', null, null, '1');
INSERT INTO `spellextra` VALUES ('18235', null, null, '1');
INSERT INTO `spellextra` VALUES ('18236', null, null, '1');
INSERT INTO `spellextra` VALUES ('18237', null, null, '1');
INSERT INTO `spellextra` VALUES ('18266', null, null, '1');
INSERT INTO `spellextra` VALUES ('18277', null, null, '1');
INSERT INTO `spellextra` VALUES ('18279', null, null, '1');
INSERT INTO `spellextra` VALUES ('18280', null, null, '1');
INSERT INTO `spellextra` VALUES ('18671', null, null, '1');
INSERT INTO `spellextra` VALUES ('22965', null, null, '1');
INSERT INTO `spellextra` VALUES ('22966', null, null, '1');
INSERT INTO `spellextra` VALUES ('27218', null, null, '1');
INSERT INTO `spellextra` VALUES ('28608', null, null, '1');
INSERT INTO `spellextra` VALUES ('29930', null, null, '1');
INSERT INTO `spellextra` VALUES ('32418', null, null, '1');
INSERT INTO `spellextra` VALUES ('37334', null, null, '1');
INSERT INTO `spellextra` VALUES ('172', null, null, '1');
INSERT INTO `spellextra` VALUES ('6222', null, null, '1');
INSERT INTO `spellextra` VALUES ('6223', null, null, '1');
INSERT INTO `spellextra` VALUES ('7648', null, null, '1');
INSERT INTO `spellextra` VALUES ('11671', null, null, '1');
INSERT INTO `spellextra` VALUES ('11672', null, null, '1');
INSERT INTO `spellextra` VALUES ('13530', null, null, '1');
INSERT INTO `spellextra` VALUES ('16402', null, null, '1');
INSERT INTO `spellextra` VALUES ('17510', null, null, '1');
INSERT INTO `spellextra` VALUES ('18088', null, null, '1');
INSERT INTO `spellextra` VALUES ('18376', null, null, '1');
INSERT INTO `spellextra` VALUES ('18656', null, null, '1');
INSERT INTO `spellextra` VALUES ('21068', null, null, '1');
INSERT INTO `spellextra` VALUES ('23439', null, null, '1');
INSERT INTO `spellextra` VALUES ('23642', null, null, '1');
INSERT INTO `spellextra` VALUES ('24910', null, null, '1');
INSERT INTO `spellextra` VALUES ('25311', null, null, '1');
INSERT INTO `spellextra` VALUES ('25805', null, null, '1');
INSERT INTO `spellextra` VALUES ('27216', null, null, '1');
INSERT INTO `spellextra` VALUES ('30938', null, null, '1');
INSERT INTO `spellextra` VALUES ('31405', null, null, '1');
INSERT INTO `spellextra` VALUES ('32063', null, null, '1');
INSERT INTO `spellextra` VALUES ('32197', null, null, '1');
INSERT INTO `spellextra` VALUES ('32644', null, null, '1');
INSERT INTO `spellextra` VALUES ('33070', null, null, '1');
INSERT INTO `spellextra` VALUES ('37113', null, null, '1');
INSERT INTO `spellextra` VALUES ('37961', null, null, '1');
INSERT INTO `spellextra` VALUES ('38219', null, null, '1');
INSERT INTO `spellextra` VALUES ('38220', null, null, '1');
INSERT INTO `spellextra` VALUES ('38221', null, null, '1');
INSERT INTO `spellextra` VALUES ('38222', null, null, '1');
INSERT INTO `spellextra` VALUES ('38230', null, null, '1');
INSERT INTO `spellextra` VALUES ('39212', null, null, '1');
INSERT INTO `spellextra` VALUES ('348', null, null, '1');
INSERT INTO `spellextra` VALUES ('707', null, null, '1');
INSERT INTO `spellextra` VALUES ('1094', null, null, '1');
INSERT INTO `spellextra` VALUES ('2941', null, null, '1');
INSERT INTO `spellextra` VALUES ('7288', null, null, '1');
INSERT INTO `spellextra` VALUES ('9034', null, null, '1');
INSERT INTO `spellextra` VALUES ('9275', null, null, '1');
INSERT INTO `spellextra` VALUES ('11665', null, null, '1');
INSERT INTO `spellextra` VALUES ('11667', null, null, '1');
INSERT INTO `spellextra` VALUES ('11668', null, null, '1');
INSERT INTO `spellextra` VALUES ('11962', null, null, '1');
INSERT INTO `spellextra` VALUES ('12742', null, null, '1');
INSERT INTO `spellextra` VALUES ('15505', null, null, '1');
INSERT INTO `spellextra` VALUES ('15570', null, null, '1');
INSERT INTO `spellextra` VALUES ('15661', null, null, '1');
INSERT INTO `spellextra` VALUES ('15732', null, null, '1');
INSERT INTO `spellextra` VALUES ('17883', null, null, '1');
INSERT INTO `spellextra` VALUES ('20294', null, null, '1');
INSERT INTO `spellextra` VALUES ('20787', null, null, '1');
INSERT INTO `spellextra` VALUES ('20800', null, null, '1');
INSERT INTO `spellextra` VALUES ('20826', null, null, '1');
INSERT INTO `spellextra` VALUES ('25309', null, null, '1');
INSERT INTO `spellextra` VALUES ('27215', null, null, '1');
INSERT INTO `spellextra` VALUES ('29928', null, null, '1');
INSERT INTO `spellextra` VALUES ('36638', null, null, '1');
INSERT INTO `spellextra` VALUES ('37628', null, null, '1');
INSERT INTO `spellextra` VALUES ('37668', null, null, '1');
INSERT INTO `spellextra` VALUES ('38806', null, null, '1');
INSERT INTO `spellextra` VALUES ('30482', null, null, '1');
INSERT INTO `spellextra` VALUES ('34913', null, null, '1');
INSERT INTO `spellextra` VALUES ('35915', null, null, '1');
INSERT INTO `spellextra` VALUES ('35916', null, null, '1');
INSERT INTO `spellextra` VALUES ('246', null, null, '1');
INSERT INTO `spellextra` VALUES ('6146', null, null, '1');
INSERT INTO `spellextra` VALUES ('10371', null, null, '1');
INSERT INTO `spellextra` VALUES ('11436', null, null, '1');
INSERT INTO `spellextra` VALUES ('13747', null, null, '1');
INSERT INTO `spellextra` VALUES ('18972', null, null, '1');
INSERT INTO `spellextra` VALUES ('19137', null, null, '1');
INSERT INTO `spellextra` VALUES ('22356', null, null, '1');
INSERT INTO `spellextra` VALUES ('24415', null, null, '1');
INSERT INTO `spellextra` VALUES ('2948', null, null, '1');
INSERT INTO `spellextra` VALUES ('5010', null, null, '1');
INSERT INTO `spellextra` VALUES ('8444', null, null, '1');
INSERT INTO `spellextra` VALUES ('8445', null, null, '1');
INSERT INTO `spellextra` VALUES ('8446', null, null, '1');
INSERT INTO `spellextra` VALUES ('10205', null, null, '1');
INSERT INTO `spellextra` VALUES ('10206', null, null, '1');
INSERT INTO `spellextra` VALUES ('10207', null, null, '1');
INSERT INTO `spellextra` VALUES ('12871', null, null, '1');
INSERT INTO `spellextra` VALUES ('13878', null, null, '1');
INSERT INTO `spellextra` VALUES ('15241', null, null, '1');
INSERT INTO `spellextra` VALUES ('17195', null, null, '1');
INSERT INTO `spellextra` VALUES ('29515', null, null, '1');
INSERT INTO `spellextra` VALUES ('11366', null, null, '1');
INSERT INTO `spellextra` VALUES ('12505', null, null, '1');
INSERT INTO `spellextra` VALUES ('12522', null, null, '1');
INSERT INTO `spellextra` VALUES ('12523', null, null, '1');
INSERT INTO `spellextra` VALUES ('12524', null, null, '1');
INSERT INTO `spellextra` VALUES ('12525', null, null, '1');
INSERT INTO `spellextra` VALUES ('12526', null, null, '1');
INSERT INTO `spellextra` VALUES ('12527', null, null, '1');
INSERT INTO `spellextra` VALUES ('17273', null, null, '1');
INSERT INTO `spellextra` VALUES ('17274', null, null, '1');
INSERT INTO `spellextra` VALUES ('18809', null, null, '1');
INSERT INTO `spellextra` VALUES ('20228', null, null, '1');
INSERT INTO `spellextra` VALUES ('24995', null, null, '1');
INSERT INTO `spellextra` VALUES ('12355', null, null, '1');
INSERT INTO `spellextra` VALUES ('12494', null, null, '1');
INSERT INTO `spellextra` VALUES ('118', null, null, '1');
INSERT INTO `spellextra` VALUES ('228', null, null, '1');
INSERT INTO `spellextra` VALUES ('851', null, null, '1');
INSERT INTO `spellextra` VALUES ('5254', null, null, '1');
INSERT INTO `spellextra` VALUES ('6345', null, null, '1');
INSERT INTO `spellextra` VALUES ('6965', null, null, '1');
INSERT INTO `spellextra` VALUES ('12824', null, null, '1');
INSERT INTO `spellextra` VALUES ('12825', null, null, '1');
INSERT INTO `spellextra` VALUES ('12826', null, null, '1');
INSERT INTO `spellextra` VALUES ('12939', null, null, '1');
INSERT INTO `spellextra` VALUES ('13323', null, null, '1');
INSERT INTO `spellextra` VALUES ('14621', null, null, '1');
INSERT INTO `spellextra` VALUES ('15534', null, null, '1');
INSERT INTO `spellextra` VALUES ('27760', null, null, '1');
INSERT INTO `spellextra` VALUES ('28270', null, null, '1');
INSERT INTO `spellextra` VALUES ('28271', null, null, '1');
INSERT INTO `spellextra` VALUES ('28272', null, null, '1');
INSERT INTO `spellextra` VALUES ('29124', null, null, '1');
INSERT INTO `spellextra` VALUES ('29183', null, null, '1');
INSERT INTO `spellextra` VALUES ('29848', null, null, '1');
INSERT INTO `spellextra` VALUES ('5143', null, null, '1');
INSERT INTO `spellextra` VALUES ('5144', null, null, '1');
INSERT INTO `spellextra` VALUES ('5145', null, null, '1');
INSERT INTO `spellextra` VALUES ('7269', null, null, '1');
INSERT INTO `spellextra` VALUES ('7270', null, null, '1');
INSERT INTO `spellextra` VALUES ('8416', null, null, '1');
INSERT INTO `spellextra` VALUES ('8417', null, null, '1');
INSERT INTO `spellextra` VALUES ('8418', null, null, '1');
INSERT INTO `spellextra` VALUES ('8419', null, null, '1');
INSERT INTO `spellextra` VALUES ('10211', null, null, '1');
INSERT INTO `spellextra` VALUES ('10212', null, null, '1');
INSERT INTO `spellextra` VALUES ('10273', null, null, '1');
INSERT INTO `spellextra` VALUES ('10274', null, null, '1');
INSERT INTO `spellextra` VALUES ('15735', null, null, '1');
INSERT INTO `spellextra` VALUES ('15736', null, null, '1');
INSERT INTO `spellextra` VALUES ('15790', null, null, '1');
INSERT INTO `spellextra` VALUES ('15791', null, null, '1');
INSERT INTO `spellextra` VALUES ('22272', null, null, '1');
INSERT INTO `spellextra` VALUES ('22273', null, null, '1');
INSERT INTO `spellextra` VALUES ('25345', null, null, '1');
INSERT INTO `spellextra` VALUES ('25346', null, null, '1');
INSERT INTO `spellextra` VALUES ('31751', null, null, '1');
INSERT INTO `spellextra` VALUES ('2480', null, null, '1');
INSERT INTO `spellextra` VALUES ('6660', null, null, '1');
INSERT INTO `spellextra` VALUES ('7918', null, null, '1');
INSERT INTO `spellextra` VALUES ('7919', null, null, '1');
INSERT INTO `spellextra` VALUES ('8995', null, null, '1');
INSERT INTO `spellextra` VALUES ('8996', null, null, '1');
INSERT INTO `spellextra` VALUES ('8997', null, null, '1');
INSERT INTO `spellextra` VALUES ('9008', null, null, '1');
INSERT INTO `spellextra` VALUES ('15547', null, null, '1');
INSERT INTO `spellextra` VALUES ('15620', null, null, '1');
INSERT INTO `spellextra` VALUES ('16100', null, null, '1');
INSERT INTO `spellextra` VALUES ('16496', null, null, '1');
INSERT INTO `spellextra` VALUES ('16572', null, null, '1');
INSERT INTO `spellextra` VALUES ('16767', null, null, '1');
INSERT INTO `spellextra` VALUES ('16768', null, null, '1');
INSERT INTO `spellextra` VALUES ('16772', null, null, '1');
INSERT INTO `spellextra` VALUES ('16775', null, null, '1');
INSERT INTO `spellextra` VALUES ('16776', null, null, '1');
INSERT INTO `spellextra` VALUES ('16777', null, null, '1');
INSERT INTO `spellextra` VALUES ('16778', null, null, '1');
INSERT INTO `spellextra` VALUES ('16779', null, null, '1');
INSERT INTO `spellextra` VALUES ('16780', null, null, '1');
INSERT INTO `spellextra` VALUES ('17353', null, null, '1');
INSERT INTO `spellextra` VALUES ('18561', null, null, '1');
INSERT INTO `spellextra` VALUES ('19881', null, null, '1');
INSERT INTO `spellextra` VALUES ('20463', null, null, '1');
INSERT INTO `spellextra` VALUES ('22121', null, null, '1');
INSERT INTO `spellextra` VALUES ('22411', null, null, '1');
INSERT INTO `spellextra` VALUES ('22907', null, null, '1');
INSERT INTO `spellextra` VALUES ('23073', null, null, '1');
INSERT INTO `spellextra` VALUES ('23337', null, null, '1');
INSERT INTO `spellextra` VALUES ('25030', null, null, '1');
INSERT INTO `spellextra` VALUES ('25031', null, null, '1');
INSERT INTO `spellextra` VALUES ('25200', null, null, '1');
INSERT INTO `spellextra` VALUES ('26282', null, null, '1');
INSERT INTO `spellextra` VALUES ('28317', null, null, '1');
INSERT INTO `spellextra` VALUES ('6136', null, null, '1');
INSERT INTO `spellextra` VALUES ('7321', null, null, '1');
INSERT INTO `spellextra` VALUES ('12484', null, null, '1');
INSERT INTO `spellextra` VALUES ('12485', null, null, '1');
INSERT INTO `spellextra` VALUES ('12486', null, null, '1');
INSERT INTO `spellextra` VALUES ('15850', null, null, '1');
INSERT INTO `spellextra` VALUES ('16927', null, null, '1');
INSERT INTO `spellextra` VALUES ('18101', null, null, '1');
INSERT INTO `spellextra` VALUES ('20005', null, null, '1');
INSERT INTO `spellextra` VALUES ('19820', null, null, '1');
INSERT INTO `spellextra` VALUES ('22570', null, null, '1');
INSERT INTO `spellextra` VALUES ('22689', null, null, '1');
INSERT INTO `spellextra` VALUES ('9007', null, null, '1');
INSERT INTO `spellextra` VALUES ('9824', null, null, '1');
INSERT INTO `spellextra` VALUES ('9826', null, null, '1');
INSERT INTO `spellextra` VALUES ('22568', null, null, '1');
INSERT INTO `spellextra` VALUES ('22827', null, null, '1');
INSERT INTO `spellextra` VALUES ('22828', null, null, '1');
INSERT INTO `spellextra` VALUES ('22829', null, null, '1');
INSERT INTO `spellextra` VALUES ('22851', null, null, '1');
INSERT INTO `spellextra` VALUES ('22853', null, null, '1');
INSERT INTO `spellextra` VALUES ('22861', null, null, '1');
INSERT INTO `spellextra` VALUES ('22862', null, null, '1');
INSERT INTO `spellextra` VALUES ('27557', null, null, '1');
INSERT INTO `spellextra` VALUES ('31018', null, null, '1');
INSERT INTO `spellextra` VALUES ('17253', null, null, '1');
INSERT INTO `spellextra` VALUES ('17255', null, null, '1');
INSERT INTO `spellextra` VALUES ('17256', null, null, '1');
INSERT INTO `spellextra` VALUES ('17257', null, null, '1');
INSERT INTO `spellextra` VALUES ('17258', null, null, '1');
INSERT INTO `spellextra` VALUES ('17259', null, null, '1');
INSERT INTO `spellextra` VALUES ('17260', null, null, '1');
INSERT INTO `spellextra` VALUES ('17261', null, null, '1');
INSERT INTO `spellextra` VALUES ('3242', null, null, '1');
INSERT INTO `spellextra` VALUES ('3446', null, null, '1');
INSERT INTO `spellextra` VALUES ('8391', null, null, '1');
INSERT INTO `spellextra` VALUES ('24213', null, null, '1');
INSERT INTO `spellextra` VALUES ('24333', null, null, '1');
INSERT INTO `spellextra` VALUES ('770', null, null, '1');
INSERT INTO `spellextra` VALUES ('778', null, null, '1');
INSERT INTO `spellextra` VALUES ('1069', null, null, '1');
INSERT INTO `spellextra` VALUES ('2887', null, null, '1');
INSERT INTO `spellextra` VALUES ('2888', null, null, '1');
INSERT INTO `spellextra` VALUES ('6950', null, null, '1');
INSERT INTO `spellextra` VALUES ('9749', null, null, '1');
INSERT INTO `spellextra` VALUES ('9907', null, null, '1');
INSERT INTO `spellextra` VALUES ('13424', null, null, '1');
INSERT INTO `spellextra` VALUES ('13752', null, null, '1');
INSERT INTO `spellextra` VALUES ('16498', null, null, '1');
INSERT INTO `spellextra` VALUES ('16855', null, null, '1');
INSERT INTO `spellextra` VALUES ('16857', null, null, '1');
INSERT INTO `spellextra` VALUES ('17387', null, null, '1');
INSERT INTO `spellextra` VALUES ('17388', null, null, '1');
INSERT INTO `spellextra` VALUES ('17389', null, null, '1');
INSERT INTO `spellextra` VALUES ('17390', null, null, '1');
INSERT INTO `spellextra` VALUES ('17391', null, null, '1');
INSERT INTO `spellextra` VALUES ('17392', null, null, '1');
INSERT INTO `spellextra` VALUES ('20656', null, null, '1');
INSERT INTO `spellextra` VALUES ('21670', null, null, '1');
INSERT INTO `spellextra` VALUES ('1822', null, null, '1');
INSERT INTO `spellextra` VALUES ('1823', null, null, '1');
INSERT INTO `spellextra` VALUES ('1824', null, null, '1');
INSERT INTO `spellextra` VALUES ('9904', null, null, '1');
INSERT INTO `spellextra` VALUES ('22639', null, null, '1');
INSERT INTO `spellextra` VALUES ('24331', null, null, '1');
INSERT INTO `spellextra` VALUES ('24332', null, null, '1');
INSERT INTO `spellextra` VALUES ('27556', null, null, '1');
INSERT INTO `spellextra` VALUES ('27638', null, null, '1');
INSERT INTO `spellextra` VALUES ('2908', null, null, '1');
INSERT INTO `spellextra` VALUES ('8955', null, null, '1');
INSERT INTO `spellextra` VALUES ('9901', null, null, '1');
INSERT INTO `spellextra` VALUES ('3252', null, null, '1');
INSERT INTO `spellextra` VALUES ('27555', null, null, '1');
INSERT INTO `spellextra` VALUES ('5570', null, null, '1');
INSERT INTO `spellextra` VALUES ('24974', null, null, '1');
INSERT INTO `spellextra` VALUES ('24975', null, null, '1');
INSERT INTO `spellextra` VALUES ('24976', null, null, '1');
INSERT INTO `spellextra` VALUES ('24977', null, null, '1');
INSERT INTO `spellextra` VALUES ('2912', null, null, '1');
INSERT INTO `spellextra` VALUES ('8949', null, null, '1');
INSERT INTO `spellextra` VALUES ('8950', null, null, '1');
INSERT INTO `spellextra` VALUES ('8951', null, null, '1');
INSERT INTO `spellextra` VALUES ('9875', null, null, '1');
INSERT INTO `spellextra` VALUES ('9876', null, null, '1');
INSERT INTO `spellextra` VALUES ('16922', null, null, '1');
INSERT INTO `spellextra` VALUES ('21668', null, null, '1');
INSERT INTO `spellextra` VALUES ('25298', null, null, '1');
INSERT INTO `spellextra` VALUES ('1079', null, null, '1');
INSERT INTO `spellextra` VALUES ('9492', null, null, '1');
INSERT INTO `spellextra` VALUES ('9493', null, null, '1');
INSERT INTO `spellextra` VALUES ('9752', null, null, '1');
INSERT INTO `spellextra` VALUES ('9894', null, null, '1');
INSERT INTO `spellextra` VALUES ('9896', null, null, '1');
INSERT INTO `spellextra` VALUES ('1082', null, null, '1');
INSERT INTO `spellextra` VALUES ('1179', null, null, '1');
INSERT INTO `spellextra` VALUES ('1849', null, null, '1');
INSERT INTO `spellextra` VALUES ('2596', null, null, '1');
INSERT INTO `spellextra` VALUES ('3009', null, null, '1');
INSERT INTO `spellextra` VALUES ('3010', null, null, '1');
INSERT INTO `spellextra` VALUES ('3029', null, null, '1');
INSERT INTO `spellextra` VALUES ('3130', null, null, '1');
INSERT INTO `spellextra` VALUES ('3133', null, null, '1');
INSERT INTO `spellextra` VALUES ('3263', null, null, '1');
INSERT INTO `spellextra` VALUES ('5201', null, null, '1');
INSERT INTO `spellextra` VALUES ('5256', null, null, '1');
INSERT INTO `spellextra` VALUES ('5424', null, null, '1');
INSERT INTO `spellextra` VALUES ('7656', null, null, '1');
INSERT INTO `spellextra` VALUES ('7657', null, null, '1');
INSERT INTO `spellextra` VALUES ('8320', null, null, '1');
INSERT INTO `spellextra` VALUES ('9849', null, null, '1');
INSERT INTO `spellextra` VALUES ('9850', null, null, '1');
INSERT INTO `spellextra` VALUES ('10617', null, null, '1');
INSERT INTO `spellextra` VALUES ('12538', null, null, '1');
INSERT INTO `spellextra` VALUES ('14804', null, null, '1');
INSERT INTO `spellextra` VALUES ('15608', null, null, '1');
INSERT INTO `spellextra` VALUES ('16553', null, null, '1');
INSERT INTO `spellextra` VALUES ('16827', null, null, '1');
INSERT INTO `spellextra` VALUES ('16828', null, null, '1');
INSERT INTO `spellextra` VALUES ('16829', null, null, '1');
INSERT INTO `spellextra` VALUES ('16830', null, null, '1');
INSERT INTO `spellextra` VALUES ('16831', null, null, '1');
INSERT INTO `spellextra` VALUES ('16832', null, null, '1');
INSERT INTO `spellextra` VALUES ('17011', null, null, '1');
INSERT INTO `spellextra` VALUES ('17470', null, null, '1');
INSERT INTO `spellextra` VALUES ('19597', null, null, '1');
INSERT INTO `spellextra` VALUES ('24187', null, null, '1');
INSERT INTO `spellextra` VALUES ('28663', null, null, '1');
INSERT INTO `spellextra` VALUES ('28750', null, null, '1');
INSERT INTO `spellextra` VALUES ('2637', null, null, '1');
INSERT INTO `spellextra` VALUES ('18657', null, null, '1');
INSERT INTO `spellextra` VALUES ('18658', null, null, '1');
INSERT INTO `spellextra` VALUES ('5211', null, null, '1');
INSERT INTO `spellextra` VALUES ('6798', null, null, '1');
INSERT INTO `spellextra` VALUES ('8983', null, null, '1');
INSERT INTO `spellextra` VALUES ('21052', null, null, '1');
INSERT INTO `spellextra` VALUES ('25515', null, null, '1');
INSERT INTO `spellextra` VALUES ('8921', null, null, '1');
INSERT INTO `spellextra` VALUES ('8924', null, null, '1');
INSERT INTO `spellextra` VALUES ('8925', null, null, '1');
INSERT INTO `spellextra` VALUES ('8926', null, null, '1');
INSERT INTO `spellextra` VALUES ('8927', null, null, '1');
INSERT INTO `spellextra` VALUES ('8928', null, null, '1');
INSERT INTO `spellextra` VALUES ('8929', null, null, '1');
INSERT INTO `spellextra` VALUES ('9833', null, null, '1');
INSERT INTO `spellextra` VALUES ('9834', null, null, '1');
INSERT INTO `spellextra` VALUES ('9835', null, null, '1');
INSERT INTO `spellextra` VALUES ('15798', null, null, '1');
INSERT INTO `spellextra` VALUES ('20690', null, null, '1');
INSERT INTO `spellextra` VALUES ('21669', null, null, '1');
INSERT INTO `spellextra` VALUES ('22206', null, null, '1');
INSERT INTO `spellextra` VALUES ('23380', null, null, '1');
INSERT INTO `spellextra` VALUES ('24957', null, null, '1');
INSERT INTO `spellextra` VALUES ('26386', null, null, '1');
INSERT INTO `spellextra` VALUES ('27737', null, null, '1');
INSERT INTO `spellextra` VALUES ('2812', null, null, '1');
INSERT INTO `spellextra` VALUES ('5176', null, null, '1');
INSERT INTO `spellextra` VALUES ('5177', null, null, '1');
INSERT INTO `spellextra` VALUES ('5178', null, null, '1');
INSERT INTO `spellextra` VALUES ('5179', null, null, '1');
INSERT INTO `spellextra` VALUES ('5180', null, null, '1');
INSERT INTO `spellextra` VALUES ('6780', null, null, '1');
INSERT INTO `spellextra` VALUES ('8905', null, null, '1');
INSERT INTO `spellextra` VALUES ('9739', null, null, '1');
INSERT INTO `spellextra` VALUES ('9912', null, null, '1');
INSERT INTO `spellextra` VALUES ('10318', null, null, '1');
INSERT INTO `spellextra` VALUES ('12964', null, null, '1');
INSERT INTO `spellextra` VALUES ('13009', null, null, '1');
INSERT INTO `spellextra` VALUES ('16559', null, null, '1');
INSERT INTO `spellextra` VALUES ('16560', null, null, '1');
INSERT INTO `spellextra` VALUES ('17144', null, null, '1');
INSERT INTO `spellextra` VALUES ('18104', null, null, '1');
INSERT INTO `spellextra` VALUES ('19574', null, null, '1');
INSERT INTO `spellextra` VALUES ('20566', null, null, '1');
INSERT INTO `spellextra` VALUES ('20698', null, null, '1');
INSERT INTO `spellextra` VALUES ('21667', null, null, '1');
INSERT INTO `spellextra` VALUES ('21807', null, null, '1');
INSERT INTO `spellextra` VALUES ('21887', null, null, '1');
INSERT INTO `spellextra` VALUES ('21977', null, null, '1');
INSERT INTO `spellextra` VALUES ('23979', null, null, '1');
INSERT INTO `spellextra` VALUES ('24395', null, null, '1');
INSERT INTO `spellextra` VALUES ('24396', null, null, '1');
INSERT INTO `spellextra` VALUES ('24397', null, null, '1');
INSERT INTO `spellextra` VALUES ('26121', null, null, '1');
INSERT INTO `spellextra` VALUES ('26592', null, null, '1');
INSERT INTO `spellextra` VALUES ('27286', null, null, '1');
INSERT INTO `spellextra` VALUES ('27499', null, null, '1');
INSERT INTO `spellextra` VALUES ('28883', null, null, '1');
INSERT INTO `spellextra` VALUES ('29214', null, null, '1');
INSERT INTO `spellextra` VALUES ('4043', null, null, '1');
INSERT INTO `spellextra` VALUES ('9435', null, null, '1');
INSERT INTO `spellextra` VALUES ('9575', null, null, '1');
INSERT INTO `spellextra` VALUES ('11815', null, null, '1');
INSERT INTO `spellextra` VALUES ('22438', null, null, '1');
INSERT INTO `spellextra` VALUES ('22439', null, null, '1');
INSERT INTO `spellextra` VALUES ('23722', null, null, '1');
INSERT INTO `spellextra` VALUES ('25099', null, null, '1');
INSERT INTO `spellextra` VALUES ('27820', null, null, '1');
INSERT INTO `spellextra` VALUES ('24530', null, null, '1');
INSERT INTO `spellextra` VALUES ('17962', null, null, '1');
INSERT INTO `spellextra` VALUES ('18930', null, null, '1');
INSERT INTO `spellextra` VALUES ('18931', null, null, '1');
INSERT INTO `spellextra` VALUES ('18932', null, null, '1');
INSERT INTO `spellextra` VALUES ('315', null, null, '1');
INSERT INTO `spellextra` VALUES ('545', null, null, '1');
INSERT INTO `spellextra` VALUES ('899', null, null, '1');
INSERT INTO `spellextra` VALUES ('923', null, null, '1');
INSERT INTO `spellextra` VALUES ('951', null, null, '1');
INSERT INTO `spellextra` VALUES ('1940', null, null, '1');
INSERT INTO `spellextra` VALUES ('2136', null, null, '1');
INSERT INTO `spellextra` VALUES ('2137', null, null, '1');
INSERT INTO `spellextra` VALUES ('2138', null, null, '1');
INSERT INTO `spellextra` VALUES ('5648', null, null, '1');
INSERT INTO `spellextra` VALUES ('5649', null, null, '1');
INSERT INTO `spellextra` VALUES ('7101', null, null, '1');
INSERT INTO `spellextra` VALUES ('8412', null, null, '1');
INSERT INTO `spellextra` VALUES ('8413', null, null, '1');
INSERT INTO `spellextra` VALUES ('8598', null, null, '1');
INSERT INTO `spellextra` VALUES ('10197', null, null, '1');
INSERT INTO `spellextra` VALUES ('10199', null, null, '1');
INSERT INTO `spellextra` VALUES ('10419', null, null, '1');
INSERT INTO `spellextra` VALUES ('10420', null, null, '1');
INSERT INTO `spellextra` VALUES ('10833', null, null, '1');
INSERT INTO `spellextra` VALUES ('11113', null, null, '1');
INSERT INTO `spellextra` VALUES ('11264', null, null, '1');
INSERT INTO `spellextra` VALUES ('11891', null, null, '1');
INSERT INTO `spellextra` VALUES ('13018', null, null, '1');
INSERT INTO `spellextra` VALUES ('13019', null, null, '1');
INSERT INTO `spellextra` VALUES ('13020', null, null, '1');
INSERT INTO `spellextra` VALUES ('13021', null, null, '1');
INSERT INTO `spellextra` VALUES ('13339', null, null, '1');
INSERT INTO `spellextra` VALUES ('13340', null, null, '1');
INSERT INTO `spellextra` VALUES ('13341', null, null, '1');
INSERT INTO `spellextra` VALUES ('13342', null, null, '1');
INSERT INTO `spellextra` VALUES ('13374', null, null, '1');
INSERT INTO `spellextra` VALUES ('14105', null, null, '1');
INSERT INTO `spellextra` VALUES ('14145', null, null, '1');
INSERT INTO `spellextra` VALUES ('15040', null, null, '1');
INSERT INTO `spellextra` VALUES ('15091', null, null, '1');
INSERT INTO `spellextra` VALUES ('15095', null, null, '1');
INSERT INTO `spellextra` VALUES ('15574', null, null, '1');
INSERT INTO `spellextra` VALUES ('15744', null, null, '1');
INSERT INTO `spellextra` VALUES ('15878', null, null, '1');
INSERT INTO `spellextra` VALUES ('16046', null, null, '1');
INSERT INTO `spellextra` VALUES ('16067', null, null, '1');
INSERT INTO `spellextra` VALUES ('16144', null, null, '1');
INSERT INTO `spellextra` VALUES ('16407', null, null, '1');
INSERT INTO `spellextra` VALUES ('16454', null, null, '1');
INSERT INTO `spellextra` VALUES ('17145', null, null, '1');
INSERT INTO `spellextra` VALUES ('17277', null, null, '1');
INSERT INTO `spellextra` VALUES ('17368', null, null, '1');
INSERT INTO `spellextra` VALUES ('17372', null, null, '1');
INSERT INTO `spellextra` VALUES ('18085', null, null, '1');
INSERT INTO `spellextra` VALUES ('18091', null, null, '1');
INSERT INTO `spellextra` VALUES ('18092', null, null, '1');
INSERT INTO `spellextra` VALUES ('18204', null, null, '1');
INSERT INTO `spellextra` VALUES ('18276', null, null, '1');
INSERT INTO `spellextra` VALUES ('18396', null, null, '1');
INSERT INTO `spellextra` VALUES ('18398', null, null, '1');
INSERT INTO `spellextra` VALUES ('19260', null, null, '1');
INSERT INTO `spellextra` VALUES ('20229', null, null, '1');
INSERT INTO `spellextra` VALUES ('20565', null, null, '1');
INSERT INTO `spellextra` VALUES ('20623', null, null, '1');
INSERT INTO `spellextra` VALUES ('20679', null, null, '1');
INSERT INTO `spellextra` VALUES ('20795', null, null, '1');
INSERT INTO `spellextra` VALUES ('20832', null, null, '1');
INSERT INTO `spellextra` VALUES ('20869', null, null, '1');
INSERT INTO `spellextra` VALUES ('20883', null, null, '1');
INSERT INTO `spellextra` VALUES ('22424', null, null, '1');
INSERT INTO `spellextra` VALUES ('22893', null, null, '1');
INSERT INTO `spellextra` VALUES ('22920', null, null, '1');
INSERT INTO `spellextra` VALUES ('22940', null, null, '1');
INSERT INTO `spellextra` VALUES ('23039', null, null, '1');
INSERT INTO `spellextra` VALUES ('23113', null, null, '1');
INSERT INTO `spellextra` VALUES ('23269', null, null, '1');
INSERT INTO `spellextra` VALUES ('23331', null, null, '1');
INSERT INTO `spellextra` VALUES ('24857', null, null, '1');
INSERT INTO `spellextra` VALUES ('24993', null, null, '1');
INSERT INTO `spellextra` VALUES ('25028', null, null, '1');
INSERT INTO `spellextra` VALUES ('25049', null, null, '1');
INSERT INTO `spellextra` VALUES ('25907', null, null, '1');
INSERT INTO `spellextra` VALUES ('26102', null, null, '1');
INSERT INTO `spellextra` VALUES ('26458', null, null, '1');
INSERT INTO `spellextra` VALUES ('27808', null, null, '1');
INSERT INTO `spellextra` VALUES ('27812', null, null, '1');
INSERT INTO `spellextra` VALUES ('28457', null, null, '1');
INSERT INTO `spellextra` VALUES ('29644', null, null, '1');
INSERT INTO `spellextra` VALUES ('31378', null, null, '1');
INSERT INTO `spellextra` VALUES ('116', null, null, '1');
INSERT INTO `spellextra` VALUES ('205', null, null, '1');
INSERT INTO `spellextra` VALUES ('403', null, null, '1');
INSERT INTO `spellextra` VALUES ('529', null, null, '1');
INSERT INTO `spellextra` VALUES ('548', null, null, '1');
INSERT INTO `spellextra` VALUES ('686', null, null, '1');
INSERT INTO `spellextra` VALUES ('690', null, null, '1');
INSERT INTO `spellextra` VALUES ('695', null, null, '1');
INSERT INTO `spellextra` VALUES ('701', null, null, '1');
INSERT INTO `spellextra` VALUES ('705', null, null, '1');
INSERT INTO `spellextra` VALUES ('837', null, null, '1');
INSERT INTO `spellextra` VALUES ('915', null, null, '1');
INSERT INTO `spellextra` VALUES ('943', null, null, '1');
INSERT INTO `spellextra` VALUES ('1084', null, null, '1');
INSERT INTO `spellextra` VALUES ('1088', null, null, '1');
INSERT INTO `spellextra` VALUES ('1096', null, null, '1');
INSERT INTO `spellextra` VALUES ('1106', null, null, '1');
INSERT INTO `spellextra` VALUES ('2626', null, null, '1');
INSERT INTO `spellextra` VALUES ('3110', null, null, '1');
INSERT INTO `spellextra` VALUES ('5401', null, null, '1');
INSERT INTO `spellextra` VALUES ('6041', null, null, '1');
INSERT INTO `spellextra` VALUES ('6254', null, null, '1');
INSERT INTO `spellextra` VALUES ('6255', null, null, '1');
INSERT INTO `spellextra` VALUES ('6949', null, null, '1');
INSERT INTO `spellextra` VALUES ('7322', null, null, '1');
INSERT INTO `spellextra` VALUES ('7588', null, null, '1');
INSERT INTO `spellextra` VALUES ('7641', null, null, '1');
INSERT INTO `spellextra` VALUES ('7799', null, null, '1');
INSERT INTO `spellextra` VALUES ('7800', null, null, '1');
INSERT INTO `spellextra` VALUES ('7801', null, null, '1');
INSERT INTO `spellextra` VALUES ('7802', null, null, '1');
INSERT INTO `spellextra` VALUES ('8246', null, null, '1');
INSERT INTO `spellextra` VALUES ('8292', null, null, '1');
INSERT INTO `spellextra` VALUES ('8398', null, null, '1');
INSERT INTO `spellextra` VALUES ('8406', null, null, '1');
INSERT INTO `spellextra` VALUES ('8407', null, null, '1');
INSERT INTO `spellextra` VALUES ('8408', null, null, '1');
INSERT INTO `spellextra` VALUES ('9057', null, null, '1');
INSERT INTO `spellextra` VALUES ('9081', null, null, '1');
INSERT INTO `spellextra` VALUES ('9532', null, null, '1');
INSERT INTO `spellextra` VALUES ('9613', null, null, '1');
INSERT INTO `spellextra` VALUES ('9672', null, null, '1');
INSERT INTO `spellextra` VALUES ('9771', null, null, '1');
INSERT INTO `spellextra` VALUES ('10179', null, null, '1');
INSERT INTO `spellextra` VALUES ('10180', null, null, '1');
INSERT INTO `spellextra` VALUES ('10181', null, null, '1');
INSERT INTO `spellextra` VALUES ('10391', null, null, '1');
INSERT INTO `spellextra` VALUES ('10392', null, null, '1');
INSERT INTO `spellextra` VALUES ('11085', null, null, '1');
INSERT INTO `spellextra` VALUES ('11538', null, null, '1');
INSERT INTO `spellextra` VALUES ('11659', null, null, '1');
INSERT INTO `spellextra` VALUES ('11660', null, null, '1');
INSERT INTO `spellextra` VALUES ('11661', null, null, '1');
INSERT INTO `spellextra` VALUES ('11762', null, null, '1');
INSERT INTO `spellextra` VALUES ('11763', null, null, '1');
INSERT INTO `spellextra` VALUES ('12167', null, null, '1');
INSERT INTO `spellextra` VALUES ('12471', null, null, '1');
INSERT INTO `spellextra` VALUES ('12675', null, null, '1');
INSERT INTO `spellextra` VALUES ('12737', null, null, '1');
INSERT INTO `spellextra` VALUES ('12739', null, null, '1');
INSERT INTO `spellextra` VALUES ('13322', null, null, '1');
INSERT INTO `spellextra` VALUES ('13439', null, null, '1');
INSERT INTO `spellextra` VALUES ('13440', null, null, '1');
INSERT INTO `spellextra` VALUES ('13441', null, null, '1');
INSERT INTO `spellextra` VALUES ('13442', null, null, '1');
INSERT INTO `spellextra` VALUES ('13480', null, null, '1');
INSERT INTO `spellextra` VALUES ('13482', null, null, '1');
INSERT INTO `spellextra` VALUES ('13527', null, null, '1');
INSERT INTO `spellextra` VALUES ('13748', null, null, '1');
INSERT INTO `spellextra` VALUES ('13901', null, null, '1');
INSERT INTO `spellextra` VALUES ('14103', null, null, '1');
INSERT INTO `spellextra` VALUES ('14106', null, null, '1');
INSERT INTO `spellextra` VALUES ('14109', null, null, '1');
INSERT INTO `spellextra` VALUES ('14119', null, null, '1');
INSERT INTO `spellextra` VALUES ('14122', null, null, '1');
INSERT INTO `spellextra` VALUES ('14200', null, null, '1');
INSERT INTO `spellextra` VALUES ('14871', null, null, '1');
INSERT INTO `spellextra` VALUES ('14887', null, null, '1');
INSERT INTO `spellextra` VALUES ('15043', null, null, '1');
INSERT INTO `spellextra` VALUES ('15124', null, null, '1');
INSERT INTO `spellextra` VALUES ('15207', null, null, '1');
INSERT INTO `spellextra` VALUES ('15208', null, null, '1');
INSERT INTO `spellextra` VALUES ('15230', null, null, '1');
INSERT INTO `spellextra` VALUES ('15232', null, null, '1');
INSERT INTO `spellextra` VALUES ('15234', null, null, '1');
INSERT INTO `spellextra` VALUES ('15245', null, null, '1');
INSERT INTO `spellextra` VALUES ('15254', null, null, '1');
INSERT INTO `spellextra` VALUES ('15451', null, null, '1');
INSERT INTO `spellextra` VALUES ('15472', null, null, '1');
INSERT INTO `spellextra` VALUES ('15497', null, null, '1');
INSERT INTO `spellextra` VALUES ('15530', null, null, '1');
INSERT INTO `spellextra` VALUES ('15537', null, null, '1');
INSERT INTO `spellextra` VALUES ('15549', null, null, '1');
INSERT INTO `spellextra` VALUES ('15592', null, null, '1');
INSERT INTO `spellextra` VALUES ('15598', null, null, '1');
INSERT INTO `spellextra` VALUES ('15611', null, null, '1');
INSERT INTO `spellextra` VALUES ('15612', null, null, '1');
INSERT INTO `spellextra` VALUES ('15801', null, null, '1');
INSERT INTO `spellextra` VALUES ('15979', null, null, '1');
INSERT INTO `spellextra` VALUES ('16249', null, null, '1');
INSERT INTO `spellextra` VALUES ('16408', null, null, '1');
INSERT INTO `spellextra` VALUES ('16409', null, null, '1');
INSERT INTO `spellextra` VALUES ('16410', null, null, '1');
INSERT INTO `spellextra` VALUES ('16554', null, null, '1');
INSERT INTO `spellextra` VALUES ('16570', null, null, '1');
INSERT INTO `spellextra` VALUES ('16782', null, null, '1');
INSERT INTO `spellextra` VALUES ('16783', null, null, '1');
INSERT INTO `spellextra` VALUES ('16784', null, null, '1');
INSERT INTO `spellextra` VALUES ('16799', null, null, '1');
INSERT INTO `spellextra` VALUES ('17228', null, null, '1');
INSERT INTO `spellextra` VALUES ('17393', null, null, '1');
INSERT INTO `spellextra` VALUES ('17434', null, null, '1');
INSERT INTO `spellextra` VALUES ('17435', null, null, '1');
INSERT INTO `spellextra` VALUES ('17483', null, null, '1');
INSERT INTO `spellextra` VALUES ('17503', null, null, '1');
INSERT INTO `spellextra` VALUES ('17509', null, null, '1');
INSERT INTO `spellextra` VALUES ('17668', null, null, '1');
INSERT INTO `spellextra` VALUES ('17669', null, null, '1');
INSERT INTO `spellextra` VALUES ('18081', null, null, '1');
INSERT INTO `spellextra` VALUES ('18083', null, null, '1');
INSERT INTO `spellextra` VALUES ('18086', null, null, '1');
INSERT INTO `spellextra` VALUES ('18089', null, null, '1');
INSERT INTO `spellextra` VALUES ('18111', null, null, '1');
INSERT INTO `spellextra` VALUES ('18112', null, null, '1');
INSERT INTO `spellextra` VALUES ('18138', null, null, '1');
INSERT INTO `spellextra` VALUES ('18164', null, null, '1');
INSERT INTO `spellextra` VALUES ('18187', null, null, '1');
INSERT INTO `spellextra` VALUES ('18205', null, null, '1');
INSERT INTO `spellextra` VALUES ('18211', null, null, '1');
INSERT INTO `spellextra` VALUES ('18214', null, null, '1');
INSERT INTO `spellextra` VALUES ('18217', null, null, '1');
INSERT INTO `spellextra` VALUES ('18833', null, null, '1');
INSERT INTO `spellextra` VALUES ('19136', null, null, '1');
INSERT INTO `spellextra` VALUES ('19728', null, null, '1');
INSERT INTO `spellextra` VALUES ('19729', null, null, '1');
INSERT INTO `spellextra` VALUES ('19874', null, null, '1');
INSERT INTO `spellextra` VALUES ('20295', null, null, '1');
INSERT INTO `spellextra` VALUES ('20297', null, null, '1');
INSERT INTO `spellextra` VALUES ('20298', null, null, '1');
INSERT INTO `spellextra` VALUES ('20685', null, null, '1');
INSERT INTO `spellextra` VALUES ('20720', null, null, '1');
INSERT INTO `spellextra` VALUES ('20741', null, null, '1');
INSERT INTO `spellextra` VALUES ('20791', null, null, '1');
INSERT INTO `spellextra` VALUES ('20792', null, null, '1');
INSERT INTO `spellextra` VALUES ('20801', null, null, '1');
INSERT INTO `spellextra` VALUES ('20802', null, null, '1');
INSERT INTO `spellextra` VALUES ('20805', null, null, '1');
INSERT INTO `spellextra` VALUES ('20806', null, null, '1');
INSERT INTO `spellextra` VALUES ('20807', null, null, '1');
INSERT INTO `spellextra` VALUES ('20816', null, null, '1');
INSERT INTO `spellextra` VALUES ('20819', null, null, '1');
INSERT INTO `spellextra` VALUES ('20822', null, null, '1');
INSERT INTO `spellextra` VALUES ('20824', null, null, '1');
INSERT INTO `spellextra` VALUES ('20825', null, null, '1');
INSERT INTO `spellextra` VALUES ('20829', null, null, '1');
INSERT INTO `spellextra` VALUES ('21066', null, null, '1');
INSERT INTO `spellextra` VALUES ('21067', null, null, '1');
INSERT INTO `spellextra` VALUES ('21077', null, null, '1');
INSERT INTO `spellextra` VALUES ('21141', null, null, '1');
INSERT INTO `spellextra` VALUES ('21341', null, null, '1');
INSERT INTO `spellextra` VALUES ('21369', null, null, '1');
INSERT INTO `spellextra` VALUES ('21971', null, null, '1');
INSERT INTO `spellextra` VALUES ('22336', null, null, '1');
INSERT INTO `spellextra` VALUES ('22357', null, null, '1');
INSERT INTO `spellextra` VALUES ('22414', null, null, '1');
INSERT INTO `spellextra` VALUES ('22643', null, null, '1');
INSERT INTO `spellextra` VALUES ('22665', null, null, '1');
INSERT INTO `spellextra` VALUES ('22677', null, null, '1');
INSERT INTO `spellextra` VALUES ('22709', null, null, '1');
INSERT INTO `spellextra` VALUES ('22878', null, null, '1');
INSERT INTO `spellextra` VALUES ('22937', null, null, '1');
INSERT INTO `spellextra` VALUES ('23102', null, null, '1');
INSERT INTO `spellextra` VALUES ('23267', null, null, '1');
INSERT INTO `spellextra` VALUES ('23412', null, null, '1');
INSERT INTO `spellextra` VALUES ('23592', null, null, '1');
INSERT INTO `spellextra` VALUES ('24099', null, null, '1');
INSERT INTO `spellextra` VALUES ('24668', null, null, '1');
INSERT INTO `spellextra` VALUES ('24820', null, null, '1');
INSERT INTO `spellextra` VALUES ('24821', null, null, '1');
INSERT INTO `spellextra` VALUES ('24822', null, null, '1');
INSERT INTO `spellextra` VALUES ('24823', null, null, '1');
INSERT INTO `spellextra` VALUES ('24834', null, null, '1');
INSERT INTO `spellextra` VALUES ('24835', null, null, '1');
INSERT INTO `spellextra` VALUES ('24836', null, null, '1');
INSERT INTO `spellextra` VALUES ('24837', null, null, '1');
INSERT INTO `spellextra` VALUES ('24838', null, null, '1');
INSERT INTO `spellextra` VALUES ('24942', null, null, '1');
INSERT INTO `spellextra` VALUES ('25055', null, null, '1');
INSERT INTO `spellextra` VALUES ('25304', null, null, '1');
INSERT INTO `spellextra` VALUES ('25307', null, null, '1');
INSERT INTO `spellextra` VALUES ('25424', null, null, '1');
INSERT INTO `spellextra` VALUES ('25586', null, null, '1');
INSERT INTO `spellextra` VALUES ('25811', null, null, '1');
INSERT INTO `spellextra` VALUES ('25991', null, null, '1');
INSERT INTO `spellextra` VALUES ('26006', null, null, '1');
INSERT INTO `spellextra` VALUES ('26052', null, null, '1');
INSERT INTO `spellextra` VALUES ('26098', null, null, '1');
INSERT INTO `spellextra` VALUES ('26601', null, null, '1');
INSERT INTO `spellextra` VALUES ('27382', null, null, '1');
INSERT INTO `spellextra` VALUES ('27383', null, null, '1');
INSERT INTO `spellextra` VALUES ('27646', null, null, '1');
INSERT INTO `spellextra` VALUES ('27831', null, null, '1');
INSERT INTO `spellextra` VALUES ('28311', null, null, '1');
INSERT INTO `spellextra` VALUES ('28407', null, null, '1');
INSERT INTO `spellextra` VALUES ('28448', null, null, '1');
INSERT INTO `spellextra` VALUES ('28478', null, null, '1');
INSERT INTO `spellextra` VALUES ('28479', null, null, '1');
INSERT INTO `spellextra` VALUES ('28522', null, null, '1');
INSERT INTO `spellextra` VALUES ('28526', null, null, '1');
INSERT INTO `spellextra` VALUES ('28599', null, null, '1');
INSERT INTO `spellextra` VALUES ('28796', null, null, '1');
INSERT INTO `spellextra` VALUES ('29163', null, null, '1');
INSERT INTO `spellextra` VALUES ('29169', null, null, '1');
INSERT INTO `spellextra` VALUES ('29317', null, null, '1');
INSERT INTO `spellextra` VALUES ('29640', null, null, '1');
INSERT INTO `spellextra` VALUES ('31800', null, null, '1');
INSERT INTO `spellextra` VALUES ('1826', null, null, '1');
INSERT INTO `spellextra` VALUES ('5373', null, null, '1');
INSERT INTO `spellextra` VALUES ('10319', null, null, '1');
INSERT INTO `spellextra` VALUES ('20183', null, null, '1');
INSERT INTO `spellextra` VALUES ('20184', null, null, '1');
INSERT INTO `spellextra` VALUES ('20185', null, null, '1');
INSERT INTO `spellextra` VALUES ('20186', null, null, '1');
INSERT INTO `spellextra` VALUES ('20187', null, null, '1');
INSERT INTO `spellextra` VALUES ('20188', null, null, '1');
INSERT INTO `spellextra` VALUES ('20267', null, null, '1');
INSERT INTO `spellextra` VALUES ('20268', null, null, '1');
INSERT INTO `spellextra` VALUES ('20271', null, null, '1');
INSERT INTO `spellextra` VALUES ('20280', null, null, '1');
INSERT INTO `spellextra` VALUES ('20281', null, null, '1');
INSERT INTO `spellextra` VALUES ('20282', null, null, '1');
INSERT INTO `spellextra` VALUES ('20283', null, null, '1');
INSERT INTO `spellextra` VALUES ('20284', null, null, '1');
INSERT INTO `spellextra` VALUES ('20285', null, null, '1');
INSERT INTO `spellextra` VALUES ('20286', null, null, '1');
INSERT INTO `spellextra` VALUES ('20300', null, null, '1');
INSERT INTO `spellextra` VALUES ('20301', null, null, '1');
INSERT INTO `spellextra` VALUES ('20302', null, null, '1');
INSERT INTO `spellextra` VALUES ('20303', null, null, '1');
INSERT INTO `spellextra` VALUES ('20304', null, null, '1');
INSERT INTO `spellextra` VALUES ('20341', null, null, '1');
INSERT INTO `spellextra` VALUES ('20342', null, null, '1');
INSERT INTO `spellextra` VALUES ('20343', null, null, '1');
INSERT INTO `spellextra` VALUES ('20344', null, null, '1');
INSERT INTO `spellextra` VALUES ('20345', null, null, '1');
INSERT INTO `spellextra` VALUES ('20346', null, null, '1');
INSERT INTO `spellextra` VALUES ('20352', null, null, '1');
INSERT INTO `spellextra` VALUES ('20353', null, null, '1');
INSERT INTO `spellextra` VALUES ('20354', null, null, '1');
INSERT INTO `spellextra` VALUES ('20355', null, null, '1');
INSERT INTO `spellextra` VALUES ('20411', null, null, '1');
INSERT INTO `spellextra` VALUES ('20412', null, null, '1');
INSERT INTO `spellextra` VALUES ('20413', null, null, '1');
INSERT INTO `spellextra` VALUES ('20414', null, null, '1');
INSERT INTO `spellextra` VALUES ('20425', null, null, '1');
INSERT INTO `spellextra` VALUES ('20467', null, null, '1');
INSERT INTO `spellextra` VALUES ('20961', null, null, '1');
INSERT INTO `spellextra` VALUES ('20962', null, null, '1');
INSERT INTO `spellextra` VALUES ('20963', null, null, '1');
INSERT INTO `spellextra` VALUES ('20964', null, null, '1');
INSERT INTO `spellextra` VALUES ('20965', null, null, '1');
INSERT INTO `spellextra` VALUES ('20966', null, null, '1');
INSERT INTO `spellextra` VALUES ('20967', null, null, '1');
INSERT INTO `spellextra` VALUES ('20968', null, null, '1');
INSERT INTO `spellextra` VALUES ('21183', null, null, '1');
INSERT INTO `spellextra` VALUES ('21889', null, null, '1');
INSERT INTO `spellextra` VALUES ('23590', null, null, '1');
INSERT INTO `spellextra` VALUES ('24234', null, null, '1');
INSERT INTO `spellextra` VALUES ('25061', null, null, '1');
INSERT INTO `spellextra` VALUES ('25745', null, null, '1');
INSERT INTO `spellextra` VALUES ('25751', null, null, '1');
INSERT INTO `spellextra` VALUES ('25752', null, null, '1');
INSERT INTO `spellextra` VALUES ('25753', null, null, '1');
INSERT INTO `spellextra` VALUES ('25757', null, null, '1');
INSERT INTO `spellextra` VALUES ('25758', null, null, '1');
INSERT INTO `spellextra` VALUES ('25759', null, null, '1');
INSERT INTO `spellextra` VALUES ('25760', null, null, '1');
INSERT INTO `spellextra` VALUES ('25761', null, null, '1');
INSERT INTO `spellextra` VALUES ('25762', null, null, '1');
INSERT INTO `spellextra` VALUES ('25942', null, null, '1');
INSERT INTO `spellextra` VALUES ('25943', null, null, '1');
INSERT INTO `spellextra` VALUES ('25944', null, null, '1');
INSERT INTO `spellextra` VALUES ('25945', null, null, '1');
INSERT INTO `spellextra` VALUES ('27731', null, null, '1');
INSERT INTO `spellextra` VALUES ('133', null, null, '1');
INSERT INTO `spellextra` VALUES ('143', null, null, '1');
INSERT INTO `spellextra` VALUES ('145', null, null, '1');
INSERT INTO `spellextra` VALUES ('3140', null, null, '1');
INSERT INTO `spellextra` VALUES ('8400', null, null, '1');
INSERT INTO `spellextra` VALUES ('8401', null, null, '1');
INSERT INTO `spellextra` VALUES ('8402', null, null, '1');
INSERT INTO `spellextra` VALUES ('9053', null, null, '1');
INSERT INTO `spellextra` VALUES ('9487', null, null, '1');
INSERT INTO `spellextra` VALUES ('9488', null, null, '1');
INSERT INTO `spellextra` VALUES ('10148', null, null, '1');
INSERT INTO `spellextra` VALUES ('10149', null, null, '1');
INSERT INTO `spellextra` VALUES ('10150', null, null, '1');
INSERT INTO `spellextra` VALUES ('10151', null, null, '1');
INSERT INTO `spellextra` VALUES ('10578', null, null, '1');
INSERT INTO `spellextra` VALUES ('11839', null, null, '1');
INSERT INTO `spellextra` VALUES ('11921', null, null, '1');
INSERT INTO `spellextra` VALUES ('11985', null, null, '1');
INSERT INTO `spellextra` VALUES ('11988', null, null, '1');
INSERT INTO `spellextra` VALUES ('11989', null, null, '1');
INSERT INTO `spellextra` VALUES ('12466', null, null, '1');
INSERT INTO `spellextra` VALUES ('13140', null, null, '1');
INSERT INTO `spellextra` VALUES ('13375', null, null, '1');
INSERT INTO `spellextra` VALUES ('13438', null, null, '1');
INSERT INTO `spellextra` VALUES ('14034', null, null, '1');
INSERT INTO `spellextra` VALUES ('15228', null, null, '1');
INSERT INTO `spellextra` VALUES ('15242', null, null, '1');
INSERT INTO `spellextra` VALUES ('15243', null, null, '1');
INSERT INTO `spellextra` VALUES ('15285', null, null, '1');
INSERT INTO `spellextra` VALUES ('15536', null, null, '1');
INSERT INTO `spellextra` VALUES ('15662', null, null, '1');
INSERT INTO `spellextra` VALUES ('15665', null, null, '1');
INSERT INTO `spellextra` VALUES ('16101', null, null, '1');
INSERT INTO `spellextra` VALUES ('16250', null, null, '1');
INSERT INTO `spellextra` VALUES ('16412', null, null, '1');
INSERT INTO `spellextra` VALUES ('16413', null, null, '1');
INSERT INTO `spellextra` VALUES ('16415', null, null, '1');
INSERT INTO `spellextra` VALUES ('16788', null, null, '1');
INSERT INTO `spellextra` VALUES ('17203', null, null, '1');
INSERT INTO `spellextra` VALUES ('17290', null, null, '1');
INSERT INTO `spellextra` VALUES ('18082', null, null, '1');
INSERT INTO `spellextra` VALUES ('18105', null, null, '1');
INSERT INTO `spellextra` VALUES ('18108', null, null, '1');
INSERT INTO `spellextra` VALUES ('18199', null, null, '1');
INSERT INTO `spellextra` VALUES ('18392', null, null, '1');
INSERT INTO `spellextra` VALUES ('18796', null, null, '1');
INSERT INTO `spellextra` VALUES ('19391', null, null, '1');
INSERT INTO `spellextra` VALUES ('19816', null, null, '1');
INSERT INTO `spellextra` VALUES ('20420', null, null, '1');
INSERT INTO `spellextra` VALUES ('20678', null, null, '1');
INSERT INTO `spellextra` VALUES ('20692', null, null, '1');
INSERT INTO `spellextra` VALUES ('20714', null, null, '1');
INSERT INTO `spellextra` VALUES ('20793', null, null, '1');
INSERT INTO `spellextra` VALUES ('20797', null, null, '1');
INSERT INTO `spellextra` VALUES ('20808', null, null, '1');
INSERT INTO `spellextra` VALUES ('20811', null, null, '1');
INSERT INTO `spellextra` VALUES ('20815', null, null, '1');
INSERT INTO `spellextra` VALUES ('20823', null, null, '1');
INSERT INTO `spellextra` VALUES ('21072', null, null, '1');
INSERT INTO `spellextra` VALUES ('21159', null, null, '1');
INSERT INTO `spellextra` VALUES ('21162', null, null, '1');
INSERT INTO `spellextra` VALUES ('21230', null, null, '1');
INSERT INTO `spellextra` VALUES ('21402', null, null, '1');
INSERT INTO `spellextra` VALUES ('21549', null, null, '1');
INSERT INTO `spellextra` VALUES ('22088', null, null, '1');
INSERT INTO `spellextra` VALUES ('22425', null, null, '1');
INSERT INTO `spellextra` VALUES ('23024', null, null, '1');
INSERT INTO `spellextra` VALUES ('23411', null, null, '1');
INSERT INTO `spellextra` VALUES ('23512', null, null, '1');
INSERT INTO `spellextra` VALUES ('24374', null, null, '1');
INSERT INTO `spellextra` VALUES ('24611', null, null, '1');
INSERT INTO `spellextra` VALUES ('25306', null, null, '1');
INSERT INTO `spellextra` VALUES ('39416', null, null, '1');
INSERT INTO `spellextra` VALUES ('53', null, null, '2');
INSERT INTO `spellextra` VALUES ('703', null, null, '2');
INSERT INTO `spellextra` VALUES ('1329', null, null, '2');
INSERT INTO `spellextra` VALUES ('2589', null, null, '2');
INSERT INTO `spellextra` VALUES ('2590', null, null, '2');
INSERT INTO `spellextra` VALUES ('2591', null, null, '2');
INSERT INTO `spellextra` VALUES ('5221', null, null, '2');
INSERT INTO `spellextra` VALUES ('6785', null, null, '2');
INSERT INTO `spellextra` VALUES ('6787', null, null, '2');
INSERT INTO `spellextra` VALUES ('6800', null, null, '2');
INSERT INTO `spellextra` VALUES ('8627', null, null, '2');
INSERT INTO `spellextra` VALUES ('8631', null, null, '2');
INSERT INTO `spellextra` VALUES ('8632', null, null, '2');
INSERT INTO `spellextra` VALUES ('8633', null, null, '2');
INSERT INTO `spellextra` VALUES ('8676', null, null, '2');
INSERT INTO `spellextra` VALUES ('8721', null, null, '2');
INSERT INTO `spellextra` VALUES ('8724', null, null, '2');
INSERT INTO `spellextra` VALUES ('8725', null, null, '2');
INSERT INTO `spellextra` VALUES ('8992', null, null, '2');
INSERT INTO `spellextra` VALUES ('9829', null, null, '2');
INSERT INTO `spellextra` VALUES ('9830', null, null, '2');
INSERT INTO `spellextra` VALUES ('9866', null, null, '2');
INSERT INTO `spellextra` VALUES ('9867', null, null, '2');
INSERT INTO `spellextra` VALUES ('11267', null, null, '2');
INSERT INTO `spellextra` VALUES ('11268', null, null, '2');
INSERT INTO `spellextra` VALUES ('11269', null, null, '2');
INSERT INTO `spellextra` VALUES ('11279', null, null, '2');
INSERT INTO `spellextra` VALUES ('11280', null, null, '2');
INSERT INTO `spellextra` VALUES ('11281', null, null, '2');
INSERT INTO `spellextra` VALUES ('11289', null, null, '2');
INSERT INTO `spellextra` VALUES ('11290', null, null, '2');
INSERT INTO `spellextra` VALUES ('21987', null, null, '2');
INSERT INTO `spellextra` VALUES ('23959', null, null, '2');
INSERT INTO `spellextra` VALUES ('24825', null, null, '2');
INSERT INTO `spellextra` VALUES ('25300', null, null, '2');
INSERT INTO `spellextra` VALUES ('26839', null, null, '2');
INSERT INTO `spellextra` VALUES ('26863', null, null, '2');
INSERT INTO `spellextra` VALUES ('26884', null, null, '2');
INSERT INTO `spellextra` VALUES ('27001', null, null, '2');
INSERT INTO `spellextra` VALUES ('27002', null, null, '2');
INSERT INTO `spellextra` VALUES ('27005', null, null, '2');
INSERT INTO `spellextra` VALUES ('27441', null, null, '2');
INSERT INTO `spellextra` VALUES ('34411', null, null, '2');
INSERT INTO `spellextra` VALUES ('34412', null, null, '2');
INSERT INTO `spellextra` VALUES ('34413', null, null, '2');

-- ----------------------------
-- Table structure for `spelloverride`
-- ----------------------------
DROP TABLE IF EXISTS `spelloverride`;
CREATE TABLE `spelloverride` (
  `overrideId` int(30) NOT NULL DEFAULT '0',
  `spellId` int(30) NOT NULL DEFAULT '0',
  UNIQUE KEY `overrideId` (`overrideId`,`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of spelloverride
-- ----------------------------
INSERT INTO `spelloverride` VALUES ('836', '10');
INSERT INTO `spelloverride` VALUES ('836', '6141');
INSERT INTO `spelloverride` VALUES ('836', '8427');
INSERT INTO `spelloverride` VALUES ('836', '10185');
INSERT INTO `spelloverride` VALUES ('836', '10186');
INSERT INTO `spelloverride` VALUES ('836', '10187');
INSERT INTO `spelloverride` VALUES ('836', '27085');
INSERT INTO `spelloverride` VALUES ('836', '27618');
INSERT INTO `spelloverride` VALUES ('850', '5246');
INSERT INTO `spelloverride` VALUES ('850', '12730');
INSERT INTO `spelloverride` VALUES ('850', '19134');
INSERT INTO `spelloverride` VALUES ('850', '20511');
INSERT INTO `spelloverride` VALUES ('850', '29544');
INSERT INTO `spelloverride` VALUES ('850', '33789');
INSERT INTO `spelloverride` VALUES ('850', '38945');
INSERT INTO `spelloverride` VALUES ('850', '38946');
INSERT INTO `spelloverride` VALUES ('968', '5246');
INSERT INTO `spelloverride` VALUES ('968', '12730');
INSERT INTO `spelloverride` VALUES ('968', '19134');
INSERT INTO `spelloverride` VALUES ('968', '20511');
INSERT INTO `spelloverride` VALUES ('968', '29544');
INSERT INTO `spelloverride` VALUES ('968', '33789');
INSERT INTO `spelloverride` VALUES ('968', '38945');
INSERT INTO `spelloverride` VALUES ('968', '38946');
INSERT INTO `spelloverride` VALUES ('969', '5246');
INSERT INTO `spelloverride` VALUES ('969', '12730');
INSERT INTO `spelloverride` VALUES ('969', '19134');
INSERT INTO `spelloverride` VALUES ('969', '20511');
INSERT INTO `spelloverride` VALUES ('969', '29544');
INSERT INTO `spelloverride` VALUES ('969', '33789');
INSERT INTO `spelloverride` VALUES ('969', '38945');
INSERT INTO `spelloverride` VALUES ('969', '38946');
INSERT INTO `spelloverride` VALUES ('988', '10');
INSERT INTO `spelloverride` VALUES ('988', '6141');
INSERT INTO `spelloverride` VALUES ('988', '8427');
INSERT INTO `spelloverride` VALUES ('988', '10185');
INSERT INTO `spelloverride` VALUES ('988', '10186');
INSERT INTO `spelloverride` VALUES ('988', '10187');
INSERT INTO `spelloverride` VALUES ('988', '27085');
INSERT INTO `spelloverride` VALUES ('988', '27618');
INSERT INTO `spelloverride` VALUES ('989', '10');
INSERT INTO `spelloverride` VALUES ('989', '6141');
INSERT INTO `spelloverride` VALUES ('989', '8427');
INSERT INTO `spelloverride` VALUES ('989', '10185');
INSERT INTO `spelloverride` VALUES ('989', '10186');
INSERT INTO `spelloverride` VALUES ('989', '10187');
INSERT INTO `spelloverride` VALUES ('989', '27085');
INSERT INTO `spelloverride` VALUES ('989', '27618');
INSERT INTO `spelloverride` VALUES ('2188', '1949');
INSERT INTO `spelloverride` VALUES ('2188', '5740');
INSERT INTO `spelloverride` VALUES ('2188', '6219');
INSERT INTO `spelloverride` VALUES ('2188', '6353');
INSERT INTO `spelloverride` VALUES ('2188', '11677');
INSERT INTO `spelloverride` VALUES ('2188', '11678');
INSERT INTO `spelloverride` VALUES ('2188', '11683');
INSERT INTO `spelloverride` VALUES ('2188', '11684');
INSERT INTO `spelloverride` VALUES ('2188', '17924');
INSERT INTO `spelloverride` VALUES ('2188', '19474');
INSERT INTO `spelloverride` VALUES ('2188', '27211');
INSERT INTO `spelloverride` VALUES ('2188', '27212');
INSERT INTO `spelloverride` VALUES ('2188', '27213');
INSERT INTO `spelloverride` VALUES ('2188', '30545');
INSERT INTO `spelloverride` VALUES ('2188', '30859');
INSERT INTO `spelloverride` VALUES ('2188', '34659');
INSERT INTO `spelloverride` VALUES ('2188', '34660');
INSERT INTO `spelloverride` VALUES ('2188', '39131');
INSERT INTO `spelloverride` VALUES ('2188', '39132');
INSERT INTO `spelloverride` VALUES ('2188', '39273');
INSERT INTO `spelloverride` VALUES ('2189', '1949');
INSERT INTO `spelloverride` VALUES ('2189', '5740');
INSERT INTO `spelloverride` VALUES ('2189', '6219');
INSERT INTO `spelloverride` VALUES ('2189', '6353');
INSERT INTO `spelloverride` VALUES ('2189', '11677');
INSERT INTO `spelloverride` VALUES ('2189', '11678');
INSERT INTO `spelloverride` VALUES ('2189', '11683');
INSERT INTO `spelloverride` VALUES ('2189', '11684');
INSERT INTO `spelloverride` VALUES ('2189', '17924');
INSERT INTO `spelloverride` VALUES ('2189', '19474');
INSERT INTO `spelloverride` VALUES ('2189', '27211');
INSERT INTO `spelloverride` VALUES ('2189', '27212');
INSERT INTO `spelloverride` VALUES ('2189', '27213');
INSERT INTO `spelloverride` VALUES ('2189', '30545');
INSERT INTO `spelloverride` VALUES ('2189', '30859');
INSERT INTO `spelloverride` VALUES ('2189', '34659');
INSERT INTO `spelloverride` VALUES ('2189', '34660');
INSERT INTO `spelloverride` VALUES ('2189', '39131');
INSERT INTO `spelloverride` VALUES ('2189', '39132');
INSERT INTO `spelloverride` VALUES ('2189', '39273');
INSERT INTO `spelloverride` VALUES ('2388', '3043');
INSERT INTO `spelloverride` VALUES ('2389', '3043');
INSERT INTO `spelloverride` VALUES ('2390', '3043');
INSERT INTO `spelloverride` VALUES ('3736', '8004');
INSERT INTO `spelloverride` VALUES ('3736', '8008');
INSERT INTO `spelloverride` VALUES ('3736', '8010');
INSERT INTO `spelloverride` VALUES ('3736', '10466');
INSERT INTO `spelloverride` VALUES ('3736', '10467');
INSERT INTO `spelloverride` VALUES ('3736', '10468');
INSERT INTO `spelloverride` VALUES ('3736', '25420');
INSERT INTO `spelloverride` VALUES ('3736', '27624');
INSERT INTO `spelloverride` VALUES ('3736', '28849');
INSERT INTO `spelloverride` VALUES ('4086', '136');
INSERT INTO `spelloverride` VALUES ('4086', '3111');
INSERT INTO `spelloverride` VALUES ('4086', '3661');
INSERT INTO `spelloverride` VALUES ('4086', '3662');
INSERT INTO `spelloverride` VALUES ('4086', '13542');
INSERT INTO `spelloverride` VALUES ('4086', '13543');
INSERT INTO `spelloverride` VALUES ('4086', '13544');
INSERT INTO `spelloverride` VALUES ('4086', '27046');
INSERT INTO `spelloverride` VALUES ('4086', '33976');
INSERT INTO `spelloverride` VALUES ('4087', '136');
INSERT INTO `spelloverride` VALUES ('4087', '3111');
INSERT INTO `spelloverride` VALUES ('4087', '3661');
INSERT INTO `spelloverride` VALUES ('4087', '3662');
INSERT INTO `spelloverride` VALUES ('4087', '13542');
INSERT INTO `spelloverride` VALUES ('4087', '13543');
INSERT INTO `spelloverride` VALUES ('4087', '13544');
INSERT INTO `spelloverride` VALUES ('4087', '27046');
INSERT INTO `spelloverride` VALUES ('4087', '33976');
INSERT INTO `spelloverride` VALUES ('4235', '10');
INSERT INTO `spelloverride` VALUES ('4235', '6141');
INSERT INTO `spelloverride` VALUES ('4235', '8427');
INSERT INTO `spelloverride` VALUES ('4235', '10185');
INSERT INTO `spelloverride` VALUES ('4235', '10186');
INSERT INTO `spelloverride` VALUES ('4235', '10187');
INSERT INTO `spelloverride` VALUES ('4235', '27085');
INSERT INTO `spelloverride` VALUES ('4235', '27618');
INSERT INTO `spelloverride` VALUES ('4415', '774');
INSERT INTO `spelloverride` VALUES ('4415', '1058');
INSERT INTO `spelloverride` VALUES ('4415', '1430');
INSERT INTO `spelloverride` VALUES ('4415', '2090');
INSERT INTO `spelloverride` VALUES ('4415', '2091');
INSERT INTO `spelloverride` VALUES ('4415', '3627');
INSERT INTO `spelloverride` VALUES ('4415', '8910');
INSERT INTO `spelloverride` VALUES ('4415', '9839');
INSERT INTO `spelloverride` VALUES ('4415', '9840');
INSERT INTO `spelloverride` VALUES ('4415', '9841');
INSERT INTO `spelloverride` VALUES ('4415', '25299');
INSERT INTO `spelloverride` VALUES ('4415', '26981');
INSERT INTO `spelloverride` VALUES ('4415', '26982');
INSERT INTO `spelloverride` VALUES ('4415', '28716');
INSERT INTO `spelloverride` VALUES ('4418', '8042');
INSERT INTO `spelloverride` VALUES ('4418', '8044');
INSERT INTO `spelloverride` VALUES ('4418', '8045');
INSERT INTO `spelloverride` VALUES ('4418', '8046');
INSERT INTO `spelloverride` VALUES ('4418', '8050');
INSERT INTO `spelloverride` VALUES ('4418', '8052');
INSERT INTO `spelloverride` VALUES ('4418', '8053');
INSERT INTO `spelloverride` VALUES ('4418', '8056');
INSERT INTO `spelloverride` VALUES ('4418', '8058');
INSERT INTO `spelloverride` VALUES ('4418', '10412');
INSERT INTO `spelloverride` VALUES ('4418', '10413');
INSERT INTO `spelloverride` VALUES ('4418', '10414');
INSERT INTO `spelloverride` VALUES ('4418', '10447');
INSERT INTO `spelloverride` VALUES ('4418', '10448');
INSERT INTO `spelloverride` VALUES ('4418', '10472');
INSERT INTO `spelloverride` VALUES ('4418', '10473');
INSERT INTO `spelloverride` VALUES ('4418', '25454');
INSERT INTO `spelloverride` VALUES ('4418', '25457');
INSERT INTO `spelloverride` VALUES ('4418', '25464');
INSERT INTO `spelloverride` VALUES ('4418', '29228');
INSERT INTO `spelloverride` VALUES ('4533', '774');
INSERT INTO `spelloverride` VALUES ('4533', '1058');
INSERT INTO `spelloverride` VALUES ('4533', '1430');
INSERT INTO `spelloverride` VALUES ('4533', '2090');
INSERT INTO `spelloverride` VALUES ('4533', '2091');
INSERT INTO `spelloverride` VALUES ('4533', '3627');
INSERT INTO `spelloverride` VALUES ('4533', '8910');
INSERT INTO `spelloverride` VALUES ('4533', '9839');
INSERT INTO `spelloverride` VALUES ('4533', '9840');
INSERT INTO `spelloverride` VALUES ('4533', '9841');
INSERT INTO `spelloverride` VALUES ('4533', '25299');
INSERT INTO `spelloverride` VALUES ('4533', '26981');
INSERT INTO `spelloverride` VALUES ('4533', '26982');
INSERT INTO `spelloverride` VALUES ('4533', '28716');
INSERT INTO `spelloverride` VALUES ('4537', '8936');
INSERT INTO `spelloverride` VALUES ('4537', '8938');
INSERT INTO `spelloverride` VALUES ('4537', '8939');
INSERT INTO `spelloverride` VALUES ('4537', '8940');
INSERT INTO `spelloverride` VALUES ('4537', '8941');
INSERT INTO `spelloverride` VALUES ('4537', '9750');
INSERT INTO `spelloverride` VALUES ('4537', '9856');
INSERT INTO `spelloverride` VALUES ('4537', '9857');
INSERT INTO `spelloverride` VALUES ('4537', '9858');
INSERT INTO `spelloverride` VALUES ('4537', '26980');
INSERT INTO `spelloverride` VALUES ('4537', '28744');
INSERT INTO `spelloverride` VALUES ('4554', '403');
INSERT INTO `spelloverride` VALUES ('4554', '421');
INSERT INTO `spelloverride` VALUES ('4554', '529');
INSERT INTO `spelloverride` VALUES ('4554', '548');
INSERT INTO `spelloverride` VALUES ('4554', '915');
INSERT INTO `spelloverride` VALUES ('4554', '930');
INSERT INTO `spelloverride` VALUES ('4554', '943');
INSERT INTO `spelloverride` VALUES ('4554', '2860');
INSERT INTO `spelloverride` VALUES ('4554', '6041');
INSERT INTO `spelloverride` VALUES ('4554', '10391');
INSERT INTO `spelloverride` VALUES ('4554', '10392');
INSERT INTO `spelloverride` VALUES ('4554', '10605');
INSERT INTO `spelloverride` VALUES ('4554', '15207');
INSERT INTO `spelloverride` VALUES ('4554', '15208');
INSERT INTO `spelloverride` VALUES ('4554', '25439');
INSERT INTO `spelloverride` VALUES ('4554', '25442');
INSERT INTO `spelloverride` VALUES ('4554', '25448');
INSERT INTO `spelloverride` VALUES ('4554', '25449');
INSERT INTO `spelloverride` VALUES ('4554', '37661');
INSERT INTO `spelloverride` VALUES ('4555', '8921');
INSERT INTO `spelloverride` VALUES ('4555', '8924');
INSERT INTO `spelloverride` VALUES ('4555', '8925');
INSERT INTO `spelloverride` VALUES ('4555', '8926');
INSERT INTO `spelloverride` VALUES ('4555', '8927');
INSERT INTO `spelloverride` VALUES ('4555', '8928');
INSERT INTO `spelloverride` VALUES ('4555', '8929');
INSERT INTO `spelloverride` VALUES ('4555', '9833');
INSERT INTO `spelloverride` VALUES ('4555', '9834');
INSERT INTO `spelloverride` VALUES ('4555', '9835');
INSERT INTO `spelloverride` VALUES ('4555', '20690');
INSERT INTO `spelloverride` VALUES ('4555', '21669');
INSERT INTO `spelloverride` VALUES ('4555', '26987');
INSERT INTO `spelloverride` VALUES ('4555', '26988');
INSERT INTO `spelloverride` VALUES ('4953', '774');
INSERT INTO `spelloverride` VALUES ('4953', '1058');
INSERT INTO `spelloverride` VALUES ('4953', '1430');
INSERT INTO `spelloverride` VALUES ('4953', '2090');
INSERT INTO `spelloverride` VALUES ('4953', '2091');
INSERT INTO `spelloverride` VALUES ('4953', '3627');
INSERT INTO `spelloverride` VALUES ('4953', '8910');
INSERT INTO `spelloverride` VALUES ('4953', '9839');
INSERT INTO `spelloverride` VALUES ('4953', '9840');
INSERT INTO `spelloverride` VALUES ('4953', '9841');
INSERT INTO `spelloverride` VALUES ('4953', '25299');
INSERT INTO `spelloverride` VALUES ('4953', '26981');
INSERT INTO `spelloverride` VALUES ('4953', '26982');
INSERT INTO `spelloverride` VALUES ('4953', '28716');
INSERT INTO `spelloverride` VALUES ('4992', '689');
INSERT INTO `spelloverride` VALUES ('4992', '699');
INSERT INTO `spelloverride` VALUES ('4992', '709');
INSERT INTO `spelloverride` VALUES ('4992', '5138');
INSERT INTO `spelloverride` VALUES ('4992', '6226');
INSERT INTO `spelloverride` VALUES ('4992', '7651');
INSERT INTO `spelloverride` VALUES ('4992', '11699');
INSERT INTO `spelloverride` VALUES ('4992', '11700');
INSERT INTO `spelloverride` VALUES ('4992', '11703');
INSERT INTO `spelloverride` VALUES ('4992', '11704');
INSERT INTO `spelloverride` VALUES ('4992', '27219');
INSERT INTO `spelloverride` VALUES ('4992', '27220');
INSERT INTO `spelloverride` VALUES ('4992', '27221');
INSERT INTO `spelloverride` VALUES ('4992', '30412');
INSERT INTO `spelloverride` VALUES ('4992', '30908');
INSERT INTO `spelloverride` VALUES ('4992', '32554');
INSERT INTO `spelloverride` VALUES ('4993', '689');
INSERT INTO `spelloverride` VALUES ('4993', '699');
INSERT INTO `spelloverride` VALUES ('4993', '709');
INSERT INTO `spelloverride` VALUES ('4993', '5138');
INSERT INTO `spelloverride` VALUES ('4993', '6226');
INSERT INTO `spelloverride` VALUES ('4993', '7651');
INSERT INTO `spelloverride` VALUES ('4993', '11699');
INSERT INTO `spelloverride` VALUES ('4993', '11700');
INSERT INTO `spelloverride` VALUES ('4993', '11703');
INSERT INTO `spelloverride` VALUES ('4993', '11704');
INSERT INTO `spelloverride` VALUES ('4993', '27219');
INSERT INTO `spelloverride` VALUES ('4993', '27220');
INSERT INTO `spelloverride` VALUES ('4993', '27221');
INSERT INTO `spelloverride` VALUES ('4993', '30412');
INSERT INTO `spelloverride` VALUES ('4993', '30908');
INSERT INTO `spelloverride` VALUES ('4993', '32554');
INSERT INTO `spelloverride` VALUES ('4994', '172');
INSERT INTO `spelloverride` VALUES ('4994', '980');
INSERT INTO `spelloverride` VALUES ('4994', '1014');
INSERT INTO `spelloverride` VALUES ('4994', '6217');
INSERT INTO `spelloverride` VALUES ('4994', '6222');
INSERT INTO `spelloverride` VALUES ('4994', '6223');
INSERT INTO `spelloverride` VALUES ('4994', '7648');
INSERT INTO `spelloverride` VALUES ('4994', '11671');
INSERT INTO `spelloverride` VALUES ('4994', '11672');
INSERT INTO `spelloverride` VALUES ('4994', '11711');
INSERT INTO `spelloverride` VALUES ('4994', '11712');
INSERT INTO `spelloverride` VALUES ('4994', '11713');
INSERT INTO `spelloverride` VALUES ('4994', '18265');
INSERT INTO `spelloverride` VALUES ('4994', '18376');
INSERT INTO `spelloverride` VALUES ('4994', '18671');
INSERT INTO `spelloverride` VALUES ('4994', '18879');
INSERT INTO `spelloverride` VALUES ('4994', '18880');
INSERT INTO `spelloverride` VALUES ('4994', '18881');
INSERT INTO `spelloverride` VALUES ('4994', '21068');
INSERT INTO `spelloverride` VALUES ('4994', '23439');
INSERT INTO `spelloverride` VALUES ('4994', '23642');
INSERT INTO `spelloverride` VALUES ('4994', '25311');
INSERT INTO `spelloverride` VALUES ('4994', '27216');
INSERT INTO `spelloverride` VALUES ('4994', '27218');
INSERT INTO `spelloverride` VALUES ('4994', '27243');
INSERT INTO `spelloverride` VALUES ('4994', '27264');
INSERT INTO `spelloverride` VALUES ('4994', '27285');
INSERT INTO `spelloverride` VALUES ('4994', '28829');
INSERT INTO `spelloverride` VALUES ('4994', '30911');
INSERT INTO `spelloverride` VALUES ('4994', '30938');
INSERT INTO `spelloverride` VALUES ('4994', '31405');
INSERT INTO `spelloverride` VALUES ('4994', '32063');
INSERT INTO `spelloverride` VALUES ('4994', '32197');
INSERT INTO `spelloverride` VALUES ('4994', '32863');
INSERT INTO `spelloverride` VALUES ('4994', '32865');
INSERT INTO `spelloverride` VALUES ('4994', '35195');
INSERT INTO `spelloverride` VALUES ('4994', '36123');
INSERT INTO `spelloverride` VALUES ('4994', '37113');
INSERT INTO `spelloverride` VALUES ('4994', '38252');
INSERT INTO `spelloverride` VALUES ('4994', '39212');
INSERT INTO `spelloverride` VALUES ('4994', '39367');
INSERT INTO `spelloverride` VALUES ('5059', '585');
INSERT INTO `spelloverride` VALUES ('5059', '591');
INSERT INTO `spelloverride` VALUES ('5059', '598');
INSERT INTO `spelloverride` VALUES ('5059', '984');
INSERT INTO `spelloverride` VALUES ('5059', '1004');
INSERT INTO `spelloverride` VALUES ('5059', '6060');
INSERT INTO `spelloverride` VALUES ('5059', '8092');
INSERT INTO `spelloverride` VALUES ('5059', '8102');
INSERT INTO `spelloverride` VALUES ('5059', '8103');
INSERT INTO `spelloverride` VALUES ('5059', '8104');
INSERT INTO `spelloverride` VALUES ('5059', '8105');
INSERT INTO `spelloverride` VALUES ('5059', '8106');
INSERT INTO `spelloverride` VALUES ('5059', '10933');
INSERT INTO `spelloverride` VALUES ('5059', '10934');
INSERT INTO `spelloverride` VALUES ('5059', '10945');
INSERT INTO `spelloverride` VALUES ('5059', '10946');
INSERT INTO `spelloverride` VALUES ('5059', '10947');
INSERT INTO `spelloverride` VALUES ('5059', '25363');
INSERT INTO `spelloverride` VALUES ('5059', '25364');
INSERT INTO `spelloverride` VALUES ('5059', '25372');
INSERT INTO `spelloverride` VALUES ('5059', '25375');
INSERT INTO `spelloverride` VALUES ('5060', '585');
INSERT INTO `spelloverride` VALUES ('5060', '591');
INSERT INTO `spelloverride` VALUES ('5060', '598');
INSERT INTO `spelloverride` VALUES ('5060', '984');
INSERT INTO `spelloverride` VALUES ('5060', '1004');
INSERT INTO `spelloverride` VALUES ('5060', '6060');
INSERT INTO `spelloverride` VALUES ('5060', '8092');
INSERT INTO `spelloverride` VALUES ('5060', '8102');
INSERT INTO `spelloverride` VALUES ('5060', '8103');
INSERT INTO `spelloverride` VALUES ('5060', '8104');
INSERT INTO `spelloverride` VALUES ('5060', '8105');
INSERT INTO `spelloverride` VALUES ('5060', '8106');
INSERT INTO `spelloverride` VALUES ('5060', '10933');
INSERT INTO `spelloverride` VALUES ('5060', '10934');
INSERT INTO `spelloverride` VALUES ('5060', '10945');
INSERT INTO `spelloverride` VALUES ('5060', '10946');
INSERT INTO `spelloverride` VALUES ('5060', '10947');
INSERT INTO `spelloverride` VALUES ('5060', '25363');
INSERT INTO `spelloverride` VALUES ('5060', '25364');
INSERT INTO `spelloverride` VALUES ('5060', '25372');
INSERT INTO `spelloverride` VALUES ('5060', '25375');
INSERT INTO `spelloverride` VALUES ('5061', '17');
INSERT INTO `spelloverride` VALUES ('5061', '592');
INSERT INTO `spelloverride` VALUES ('5061', '600');
INSERT INTO `spelloverride` VALUES ('5061', '3747');
INSERT INTO `spelloverride` VALUES ('5061', '6065');
INSERT INTO `spelloverride` VALUES ('5061', '6066');
INSERT INTO `spelloverride` VALUES ('5061', '10898');
INSERT INTO `spelloverride` VALUES ('5061', '10899');
INSERT INTO `spelloverride` VALUES ('5061', '10900');
INSERT INTO `spelloverride` VALUES ('5061', '10901');
INSERT INTO `spelloverride` VALUES ('5061', '25217');
INSERT INTO `spelloverride` VALUES ('5061', '25218');
INSERT INTO `spelloverride` VALUES ('5061', '27607');
INSERT INTO `spelloverride` VALUES ('5062', '17');
INSERT INTO `spelloverride` VALUES ('5062', '592');
INSERT INTO `spelloverride` VALUES ('5062', '600');
INSERT INTO `spelloverride` VALUES ('5062', '3747');
INSERT INTO `spelloverride` VALUES ('5062', '6065');
INSERT INTO `spelloverride` VALUES ('5062', '6066');
INSERT INTO `spelloverride` VALUES ('5062', '10898');
INSERT INTO `spelloverride` VALUES ('5062', '10899');
INSERT INTO `spelloverride` VALUES ('5062', '10900');
INSERT INTO `spelloverride` VALUES ('5062', '10901');
INSERT INTO `spelloverride` VALUES ('5062', '25217');
INSERT INTO `spelloverride` VALUES ('5062', '25218');
INSERT INTO `spelloverride` VALUES ('5062', '27607');
INSERT INTO `spelloverride` VALUES ('5063', '17');
INSERT INTO `spelloverride` VALUES ('5063', '592');
INSERT INTO `spelloverride` VALUES ('5063', '600');
INSERT INTO `spelloverride` VALUES ('5063', '3747');
INSERT INTO `spelloverride` VALUES ('5063', '6065');
INSERT INTO `spelloverride` VALUES ('5063', '6066');
INSERT INTO `spelloverride` VALUES ('5063', '10898');
INSERT INTO `spelloverride` VALUES ('5063', '10899');
INSERT INTO `spelloverride` VALUES ('5063', '10900');
INSERT INTO `spelloverride` VALUES ('5063', '10901');
INSERT INTO `spelloverride` VALUES ('5063', '25217');
INSERT INTO `spelloverride` VALUES ('5063', '25218');
INSERT INTO `spelloverride` VALUES ('5063', '27607');
INSERT INTO `spelloverride` VALUES ('5064', '17');
INSERT INTO `spelloverride` VALUES ('5064', '592');
INSERT INTO `spelloverride` VALUES ('5064', '600');
INSERT INTO `spelloverride` VALUES ('5064', '3747');
INSERT INTO `spelloverride` VALUES ('5064', '6065');
INSERT INTO `spelloverride` VALUES ('5064', '6066');
INSERT INTO `spelloverride` VALUES ('5064', '10898');
INSERT INTO `spelloverride` VALUES ('5064', '10899');
INSERT INTO `spelloverride` VALUES ('5064', '10900');
INSERT INTO `spelloverride` VALUES ('5064', '10901');
INSERT INTO `spelloverride` VALUES ('5064', '25217');
INSERT INTO `spelloverride` VALUES ('5064', '25218');
INSERT INTO `spelloverride` VALUES ('5064', '27607');
INSERT INTO `spelloverride` VALUES ('5065', '17');
INSERT INTO `spelloverride` VALUES ('5065', '592');
INSERT INTO `spelloverride` VALUES ('5065', '600');
INSERT INTO `spelloverride` VALUES ('5065', '3747');
INSERT INTO `spelloverride` VALUES ('5065', '6065');
INSERT INTO `spelloverride` VALUES ('5065', '6066');
INSERT INTO `spelloverride` VALUES ('5065', '10898');
INSERT INTO `spelloverride` VALUES ('5065', '10899');
INSERT INTO `spelloverride` VALUES ('5065', '10900');
INSERT INTO `spelloverride` VALUES ('5065', '10901');
INSERT INTO `spelloverride` VALUES ('5065', '25217');
INSERT INTO `spelloverride` VALUES ('5065', '25218');
INSERT INTO `spelloverride` VALUES ('5065', '27607');
INSERT INTO `spelloverride` VALUES ('5066', '589');
INSERT INTO `spelloverride` VALUES ('5066', '594');
INSERT INTO `spelloverride` VALUES ('5066', '970');
INSERT INTO `spelloverride` VALUES ('5066', '992');
INSERT INTO `spelloverride` VALUES ('5066', '2767');
INSERT INTO `spelloverride` VALUES ('5066', '10892');
INSERT INTO `spelloverride` VALUES ('5066', '10893');
INSERT INTO `spelloverride` VALUES ('5066', '10894');
INSERT INTO `spelloverride` VALUES ('5066', '15407');
INSERT INTO `spelloverride` VALUES ('5066', '16568');
INSERT INTO `spelloverride` VALUES ('5066', '17165');
INSERT INTO `spelloverride` VALUES ('5066', '17311');
INSERT INTO `spelloverride` VALUES ('5066', '17312');
INSERT INTO `spelloverride` VALUES ('5066', '17313');
INSERT INTO `spelloverride` VALUES ('5066', '17314');
INSERT INTO `spelloverride` VALUES ('5066', '18807');
INSERT INTO `spelloverride` VALUES ('5066', '22919');
INSERT INTO `spelloverride` VALUES ('5066', '23953');
INSERT INTO `spelloverride` VALUES ('5066', '25367');
INSERT INTO `spelloverride` VALUES ('5066', '25368');
INSERT INTO `spelloverride` VALUES ('5066', '25387');
INSERT INTO `spelloverride` VALUES ('5066', '26044');
INSERT INTO `spelloverride` VALUES ('5066', '26143');
INSERT INTO `spelloverride` VALUES ('5066', '27605');
INSERT INTO `spelloverride` VALUES ('5066', '28310');
INSERT INTO `spelloverride` VALUES ('5066', '29407');
INSERT INTO `spelloverride` VALUES ('5066', '29570');
INSERT INTO `spelloverride` VALUES ('5066', '32417');
INSERT INTO `spelloverride` VALUES ('5066', '34914');
INSERT INTO `spelloverride` VALUES ('5066', '34916');
INSERT INTO `spelloverride` VALUES ('5066', '34917');
INSERT INTO `spelloverride` VALUES ('5066', '35507');
INSERT INTO `spelloverride` VALUES ('5066', '37276');
INSERT INTO `spelloverride` VALUES ('5066', '37330');
INSERT INTO `spelloverride` VALUES ('5066', '37621');
INSERT INTO `spelloverride` VALUES ('5066', '38243');
INSERT INTO `spelloverride` VALUES ('5142', '403');
INSERT INTO `spelloverride` VALUES ('5142', '421');
INSERT INTO `spelloverride` VALUES ('5142', '529');
INSERT INTO `spelloverride` VALUES ('5142', '548');
INSERT INTO `spelloverride` VALUES ('5142', '915');
INSERT INTO `spelloverride` VALUES ('5142', '930');
INSERT INTO `spelloverride` VALUES ('5142', '943');
INSERT INTO `spelloverride` VALUES ('5142', '2860');
INSERT INTO `spelloverride` VALUES ('5142', '6041');
INSERT INTO `spelloverride` VALUES ('5142', '10391');
INSERT INTO `spelloverride` VALUES ('5142', '10392');
INSERT INTO `spelloverride` VALUES ('5142', '10605');
INSERT INTO `spelloverride` VALUES ('5142', '15207');
INSERT INTO `spelloverride` VALUES ('5142', '15208');
INSERT INTO `spelloverride` VALUES ('5142', '25439');
INSERT INTO `spelloverride` VALUES ('5142', '25442');
INSERT INTO `spelloverride` VALUES ('5142', '25448');
INSERT INTO `spelloverride` VALUES ('5142', '25449');
INSERT INTO `spelloverride` VALUES ('5142', '37661');
INSERT INTO `spelloverride` VALUES ('5147', '20116');
INSERT INTO `spelloverride` VALUES ('5147', '20922');
INSERT INTO `spelloverride` VALUES ('5147', '20923');
INSERT INTO `spelloverride` VALUES ('5147', '20924');
INSERT INTO `spelloverride` VALUES ('5147', '26573');
INSERT INTO `spelloverride` VALUES ('5147', '27173');
INSERT INTO `spelloverride` VALUES ('5147', '32773');
INSERT INTO `spelloverride` VALUES ('5147', '33559');
INSERT INTO `spelloverride` VALUES ('5147', '36946');
INSERT INTO `spelloverride` VALUES ('5147', '37553');
INSERT INTO `spelloverride` VALUES ('5147', '38385');
INSERT INTO `spelloverride` VALUES ('5148', '2912');
INSERT INTO `spelloverride` VALUES ('5148', '8949');
INSERT INTO `spelloverride` VALUES ('5148', '8950');
INSERT INTO `spelloverride` VALUES ('5148', '8951');
INSERT INTO `spelloverride` VALUES ('5148', '9875');
INSERT INTO `spelloverride` VALUES ('5148', '9876');
INSERT INTO `spelloverride` VALUES ('5148', '21668');
INSERT INTO `spelloverride` VALUES ('5148', '25298');
INSERT INTO `spelloverride` VALUES ('5148', '26986');
INSERT INTO `spelloverride` VALUES ('5148', '35243');
INSERT INTO `spelloverride` VALUES ('5148', '38935');
INSERT INTO `spelloverride` VALUES ('5236', '1130');
INSERT INTO `spelloverride` VALUES ('5236', '14323');
INSERT INTO `spelloverride` VALUES ('5236', '14324');
INSERT INTO `spelloverride` VALUES ('5236', '14325');
INSERT INTO `spelloverride` VALUES ('5236', '31615');
INSERT INTO `spelloverride` VALUES ('5237', '1130');
INSERT INTO `spelloverride` VALUES ('5237', '14323');
INSERT INTO `spelloverride` VALUES ('5237', '14324');
INSERT INTO `spelloverride` VALUES ('5237', '14325');
INSERT INTO `spelloverride` VALUES ('5237', '31615');
INSERT INTO `spelloverride` VALUES ('5238', '1130');
INSERT INTO `spelloverride` VALUES ('5238', '14323');
INSERT INTO `spelloverride` VALUES ('5238', '14324');
INSERT INTO `spelloverride` VALUES ('5238', '14325');
INSERT INTO `spelloverride` VALUES ('5238', '31615');
INSERT INTO `spelloverride` VALUES ('5239', '1130');
INSERT INTO `spelloverride` VALUES ('5239', '14323');
INSERT INTO `spelloverride` VALUES ('5239', '14324');
INSERT INTO `spelloverride` VALUES ('5239', '14325');
INSERT INTO `spelloverride` VALUES ('5239', '31615');
INSERT INTO `spelloverride` VALUES ('5240', '1130');
INSERT INTO `spelloverride` VALUES ('5240', '14323');
INSERT INTO `spelloverride` VALUES ('5240', '14324');
INSERT INTO `spelloverride` VALUES ('5240', '14325');
INSERT INTO `spelloverride` VALUES ('5240', '31615');
INSERT INTO `spelloverride` VALUES ('5494', '1463');
INSERT INTO `spelloverride` VALUES ('5494', '8494');
INSERT INTO `spelloverride` VALUES ('5494', '8495');
INSERT INTO `spelloverride` VALUES ('5494', '10191');
INSERT INTO `spelloverride` VALUES ('5494', '10192');
INSERT INTO `spelloverride` VALUES ('5494', '10193');
INSERT INTO `spelloverride` VALUES ('5494', '17740');
INSERT INTO `spelloverride` VALUES ('5494', '17741');
INSERT INTO `spelloverride` VALUES ('5494', '27131');
INSERT INTO `spelloverride` VALUES ('5494', '29880');
INSERT INTO `spelloverride` VALUES ('5494', '30973');
INSERT INTO `spelloverride` VALUES ('5494', '31635');
INSERT INTO `spelloverride` VALUES ('5494', '35064');
INSERT INTO `spelloverride` VALUES ('5494', '38151');
INSERT INTO `spelloverride` VALUES ('5634', '17364');
INSERT INTO `spelloverride` VALUES ('5634', '32175');
INSERT INTO `spelloverride` VALUES ('5634', '32176');

-- ----------------------------
-- Table structure for `spells112`
-- ----------------------------
DROP TABLE IF EXISTS `spells112`;
CREATE TABLE `spells112` (
  `Id` int(100) DEFAULT '0',
  `School` int(100) DEFAULT '0',
  `Category` int(100) DEFAULT '0',
  `field4` int(100) DEFAULT '0',
  `DispelType` int(100) DEFAULT '0',
  `MechanicsType` int(100) DEFAULT '0',
  `Attributes` int(100) DEFAULT '0',
  `AttributesEx` int(100) DEFAULT '0',
  `Flags3` int(100) DEFAULT '0',
  `field10` int(100) DEFAULT '0',
  `field11` int(100) DEFAULT '0',
  `UNK12` int(100) DEFAULT '0',
  `UNK13` int(100) DEFAULT '0',
  `Targets` int(100) DEFAULT '0',
  `TargetCreatureType` int(100) DEFAULT '0',
  `RequiresSpellFocus` int(100) DEFAULT '0',
  `CasterAuraState` int(100) DEFAULT '0',
  `TargetAuraState` int(100) DEFAULT '0',
  `CastingTimeIndex` int(100) DEFAULT '0',
  `RecoveryTime` int(100) DEFAULT '0',
  `CategoryRecoveryTime` int(100) DEFAULT '0',
  `InterruptFlags` int(100) DEFAULT '0',
  `AuraInterruptFlags` int(100) DEFAULT '0',
  `ChannelInterruptFlags` int(100) DEFAULT '0',
  `procFlags` int(100) DEFAULT '0',
  `procChance` int(100) DEFAULT '0',
  `procCharges` int(100) DEFAULT '0',
  `maxLevel` int(100) DEFAULT '0',
  `baseLevel` int(100) DEFAULT '0',
  `spellLevel` int(100) DEFAULT '0',
  `DurationIndex` int(100) DEFAULT '0',
  `powerType` int(100) DEFAULT '0',
  `manaCost` int(100) DEFAULT '0',
  `manaCostPerlevel` int(100) DEFAULT '0',
  `manaPerSecond` int(100) DEFAULT '0',
  `manaPerSecondPerLevel` int(100) DEFAULT '0',
  `rangeIndex` int(100) DEFAULT '0',
  `speed` float DEFAULT '0',
  `modalNextSpell` int(100) DEFAULT '0',
  `maxstack` int(100) DEFAULT '0',
  `Totem1` int(100) DEFAULT '0',
  `Totem2` int(100) DEFAULT '0',
  `Reagent1` int(100) DEFAULT '0',
  `Reagent2` int(100) DEFAULT '0',
  `Reagent3` int(100) DEFAULT '0',
  `Reagent4` int(100) DEFAULT '0',
  `Reagent5` int(100) DEFAULT '0',
  `Reagent6` int(100) DEFAULT '0',
  `Reagent7` int(100) DEFAULT '0',
  `Reagent8` int(100) DEFAULT '0',
  `ReagentCount1` int(100) DEFAULT '0',
  `ReagentCount2` int(100) DEFAULT '0',
  `ReagentCount3` int(100) DEFAULT '0',
  `ReagentCount4` int(100) DEFAULT '0',
  `ReagentCount5` int(100) DEFAULT '0',
  `ReagentCount6` int(100) DEFAULT '0',
  `ReagentCount7` int(100) DEFAULT '0',
  `ReagentCount8` int(100) DEFAULT '0',
  `EquippedItemClass` int(100) DEFAULT '0',
  `EquippedItemSubClass` int(100) DEFAULT '0',
  `RequiredItemFlags` int(100) DEFAULT '0',
  `Effect1` int(100) DEFAULT '0',
  `Effect2` int(100) DEFAULT '0',
  `Effect3` int(100) DEFAULT '0',
  `EffectDieSides1` int(100) DEFAULT '0',
  `EffectDieSides2` int(100) DEFAULT '0',
  `EffectDieSides3` int(100) DEFAULT '0',
  `EffectBaseDice1` int(100) DEFAULT '0',
  `EffectBaseDice2` int(100) DEFAULT '0',
  `EffectBaseDice3` int(100) DEFAULT '0',
  `EffectDicePerLevel1` float DEFAULT '0',
  `EffectDicePerLevel2` float DEFAULT '0',
  `EffectDicePerLevel3` float DEFAULT '0',
  `EffectRealPointsPerLevel1` float DEFAULT '0',
  `EffectRealPointsPerLevel2` float DEFAULT '0',
  `EffectRealPointsPerLevel3` float DEFAULT '0',
  `EffectBasePoints1` int(100) DEFAULT '0',
  `EffectBasePoints2` int(100) DEFAULT '0',
  `EffectBasePoints3` int(100) DEFAULT '0',
  `Effectunk1901` int(100) DEFAULT '0',
  `Effectunk1902` int(100) DEFAULT '0',
  `Effectunk1903` int(100) DEFAULT '0',
  `EffectImplicitTargetA1` int(100) DEFAULT '0',
  `EffectImplicitTargetA2` int(100) DEFAULT '0',
  `EffectImplicitTargetA3` int(100) DEFAULT '0',
  `EffectImplicitTargetB1` int(100) DEFAULT '0',
  `EffectImplicitTargetB2` int(100) DEFAULT '0',
  `EffectImplicitTargetB3` int(100) DEFAULT '0',
  `EffectRadiusIndex1` int(100) DEFAULT '0',
  `EffectRadiusIndex2` int(100) DEFAULT '0',
  `EffectRadiusIndex3` int(100) DEFAULT '0',
  `EffectApplyAuraName1` int(100) DEFAULT '0',
  `EffectApplyAuraName2` int(100) DEFAULT '0',
  `EffectApplyAuraName3` int(100) DEFAULT '0',
  `EffectAmplitude1` int(100) DEFAULT '0',
  `EffectAmplitude2` int(100) DEFAULT '0',
  `EffectAmplitude3` int(100) DEFAULT '0',
  `Effectunknown1` float DEFAULT '0',
  `Effectunknown2` float DEFAULT '0',
  `Effectunknown3` float DEFAULT '0',
  `EffectChainTarget1` int(100) DEFAULT '0',
  `EffectChainTarget2` int(100) DEFAULT '0',
  `EffectChainTarget3` int(100) DEFAULT '0',
  `EffectSpellGroupRelation1` int(100) DEFAULT '0',
  `EffectSpellGroupRelation2` int(100) DEFAULT '0',
  `EffectSpellGroupRelation3` int(100) DEFAULT '0',
  `EffectMiscValue1` int(100) DEFAULT '0',
  `EffectMiscValue2` int(100) DEFAULT '0',
  `EffectMiscValue3` int(100) DEFAULT '0',
  `EffectTriggerSpell1` int(100) DEFAULT '0',
  `EffectTriggerSpell2` int(100) DEFAULT '0',
  `EffectTriggerSpell3` int(100) DEFAULT '0',
  `EffectPointsPerComboPoint1` float DEFAULT '0',
  `EffectPointsPerComboPoint2` float DEFAULT '0',
  `EffectPointsPerComboPoint3` float DEFAULT '0',
  `SpellVisual` int(100) DEFAULT '0',
  `field114` int(100) DEFAULT '0',
  `dummy` int(100) DEFAULT '0',
  `CoSpell` int(100) DEFAULT '0',
  `spellPriority` int(100) DEFAULT '0',
  `Name` longtext,
  `NameAlt1` longtext,
  `NameAlt2` longtext,
  `NameAlt3` longtext,
  `NameAlt4` longtext,
  `NameAlt5` longtext,
  `NameAlt6` longtext,
  `NameAlt7` longtext,
  `NameFlags` longtext,
  `Rank` longtext,
  `RankAlt1` longtext,
  `RankAlt2` longtext,
  `RankAlt3` longtext,
  `RankAlt4` longtext,
  `RankAlt5` longtext,
  `RankAlt6` longtext,
  `RankAlt7` longtext,
  `RankFlags` longtext,
  `Description` longtext,
  `DescriptionAlt1` longtext,
  `DescriptionAlt2` longtext,
  `DescriptionAlt3` longtext,
  `DescriptionAlt4` longtext,
  `DescriptionAlt5` longtext,
  `DescriptionAlt6` longtext,
  `DescriptionAlt7` longtext,
  `DescriptionFlags` longtext,
  `BuffDescription` longtext,
  `BuffDescriptionAlt1` longtext,
  `BuffDescriptionAlt2` longtext,
  `BuffDescriptionAlt3` longtext,
  `BuffDescriptionAlt4` longtext,
  `BuffDescriptionAlt5` longtext,
  `BuffDescriptionAlt6` longtext,
  `BuffDescriptionAlt7` longtext,
  `Buffdescflags` int(100) DEFAULT '0',
  `ManaCostPercentage` int(100) DEFAULT '0',
  `unkflags` int(100) DEFAULT '0',
  `StartRecoveryTime` int(100) DEFAULT '0',
  `StartRecoveryCategory` int(100) DEFAULT '0',
  `SpellFamilyName` int(100) DEFAULT '0',
  `SpellGroupType` int(100) DEFAULT '0',
  `unkne` int(100) DEFAULT '0',
  `MaxTargets` int(100) DEFAULT '0',
  `Spell_Dmg_Type` int(100) DEFAULT '0',
  `FG` int(100) DEFAULT '0',
  `FH` int(100) DEFAULT '0',
  `dmg_multiplier_1` float DEFAULT '0',
  `dmg_multiplier_2` float DEFAULT '0',
  `dmg_multiplier_3` float DEFAULT '0',
  `FL` int(100) DEFAULT '0',
  `FM` int(100) DEFAULT '0',
  `FN` int(100) DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of spells112
-- ----------------------------

-- ----------------------------
-- Table structure for `spell_disable`
-- ----------------------------
DROP TABLE IF EXISTS `spell_disable`;
CREATE TABLE `spell_disable` (
  `spellid` int(30) NOT NULL,
  `replacement_spellid` int(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of spell_disable
-- ----------------------------

-- ----------------------------
-- Table structure for `spell_disable_trainers`
-- ----------------------------
DROP TABLE IF EXISTS `spell_disable_trainers`;
CREATE TABLE `spell_disable_trainers` (
  `spellid` int(30) NOT NULL,
  `replacement_spellid` int(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of spell_disable_trainers
-- ----------------------------

-- ----------------------------
-- Table structure for `teleport_coords`
-- ----------------------------
DROP TABLE IF EXISTS `teleport_coords`;
CREATE TABLE `teleport_coords` (
  `id` int(16) NOT NULL DEFAULT '0',
  `name` char(255) NOT NULL DEFAULT '',
  `mapId` int(16) NOT NULL DEFAULT '0',
  `x` float NOT NULL DEFAULT '0',
  `y` float NOT NULL DEFAULT '0',
  `z` float NOT NULL DEFAULT '0',
  `totrigger` int(16) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of teleport_coords
-- ----------------------------
INSERT INTO `teleport_coords` VALUES ('3561', 'Teleport: Stormwind', '0', '-8913.23', '554.633', '93.7944', '0');
INSERT INTO `teleport_coords` VALUES ('3562', 'Teleport: Ironforge', '0', '-4981.25', '-881.542', '501.66', '0');
INSERT INTO `teleport_coords` VALUES ('3563', 'Teleport: Undercity', '0', '1586.48', '239.562', '-52.149', '0');
INSERT INTO `teleport_coords` VALUES ('3565', 'Teleport: Darnassus', '1', '9951.52', '2280.32', '1341.39', '0');
INSERT INTO `teleport_coords` VALUES ('3566', 'Teleport: Thunder Bluff', '1', '-1196.22', '29.0941', '176.949', '0');
INSERT INTO `teleport_coords` VALUES ('3567', 'Teleport: Orgrimmar', '1', '1676.21', '-4315.29', '61.5293', '0');
INSERT INTO `teleport_coords` VALUES ('17334', 'Portal Effect: Stormwind', '0', '-8913.23', '554.633', '93.7944', '0');
INSERT INTO `teleport_coords` VALUES ('17607', 'Portal Effect: Ironforge', '0', '-4981.25', '-881.542', '501.66', '0');
INSERT INTO `teleport_coords` VALUES ('17608', 'Portal Effect: Darnassus', '1', '9951.52', '2280.32', '1341.39', '0');
INSERT INTO `teleport_coords` VALUES ('17609', 'Portal Effect: Orgrimmar', '1', '1676.21', '-4315.29', '61.5293', '0');
INSERT INTO `teleport_coords` VALUES ('17610', 'Portal Effect: Thunder Bluff', '1', '-1196.22', '29.0941', '176.949', '0');
INSERT INTO `teleport_coords` VALUES ('17611', 'Portal Effect: Undercity', '0', '1586.48', '239.562', '-52.149', '0');
INSERT INTO `teleport_coords` VALUES ('21128', 'Portal Effect: Maraudon', '349', '428', '15', '-112', '0');
INSERT INTO `teleport_coords` VALUES ('31', 'Teleport: Goldshire', '0', '-9458.81', '64.826', '55.957', '0');
INSERT INTO `teleport_coords` VALUES ('33', 'Teleport: Westfall', '0', '-9839.9', '884.804', '27.454', '0');
INSERT INTO `teleport_coords` VALUES ('34', 'Teleport: Duskwood', '0', '-9973.92', '-1633.17', '26.94', '0');
INSERT INTO `teleport_coords` VALUES ('35', 'Teleport: Elwynn', '0', '-9760.26', '678.23', '27.021', '0');
INSERT INTO `teleport_coords` VALUES ('427', 'Teleport: Scarlet Monastery', '0', '2889.91', '-811.148', '160.332', '0');
INSERT INTO `teleport_coords` VALUES ('428', 'Teleport: Moonbrook', '0', '-11025.2', '1497.86', '43.1953', '0');
INSERT INTO `teleport_coords` VALUES ('442', 'Teleport: Northshire Abbey', '0', '-8914.38', '-135.35', '80.45', '0');
INSERT INTO `teleport_coords` VALUES ('444', 'Teleport: Westfall Lighthouse', '0', '-11409.9', '1968.42', '10.4271', '0');
INSERT INTO `teleport_coords` VALUES ('445', 'Teleport: Darkshire', '0', '-10413.9', '-1136.88', '24.1288', '0');
INSERT INTO `teleport_coords` VALUES ('446', 'Teleport: Raven Hill Cemetary', '0', '-10531.2', '296.656', '30.9649', '0');
INSERT INTO `teleport_coords` VALUES ('1936', 'Teleport: Anvilmar', '0', '-6133.84', '383.79', '395.54', '0');
INSERT INTO `teleport_coords` VALUES ('4996', '[PH] Teleport to Orgrimmar', '1', '1676.21', '-4315.29', '61.5293', '0');
INSERT INTO `teleport_coords` VALUES ('4997', '[PH] Teleport to Booty Bay', '0', '-14319.3', '442.7', '22.94', '0');
INSERT INTO `teleport_coords` VALUES ('4998', '[PH] Teleport to Grom\'Gol', '0', '-12372.7', '204', '3.07', '0');
INSERT INTO `teleport_coords` VALUES ('4999', '[PH] Teleport to Ratchet', '1', '-994.248', '-3830.1', '7', '0');
INSERT INTO `teleport_coords` VALUES ('5000', '[PH] Teleport to Undercity', '0', '1586.48', '239.562', '-52.149', '0');
INSERT INTO `teleport_coords` VALUES ('6348', '[PH] Teleport to Menethil Harbor', '0', '-3761.54', '-734.7', '8.04', '0');
INSERT INTO `teleport_coords` VALUES ('6349', '[PH] Teleport to Auberdine', '1', '6426.77', '398.89', '10.96', '0');
INSERT INTO `teleport_coords` VALUES ('6483', '[PH] Teleport to Felwood', '1', '6200', '-1035', '387', '0');
INSERT INTO `teleport_coords` VALUES ('6484', '[PH] Teleport to Balthule', '1', '7245', '-652', '35', '0');
INSERT INTO `teleport_coords` VALUES ('6719', '[PH] Teleport to Theramore', '1', '-3717.96', '-4406.17', '23.12', '0');
INSERT INTO `teleport_coords` VALUES ('8735', '[PH] Teleport to Blackfathom Deeps', '1', '4127.5', '867.8', '9.69', '0');
INSERT INTO `teleport_coords` VALUES ('9268', 'Teleport to Darnassus - Event', '1', '9951.52', '2280.32', '1341.39', '0');
INSERT INTO `teleport_coords` VALUES ('11362', 'Teleport to Gnomeregan', '0', '-5183.1', '602.77', '409.11', '0');
INSERT INTO `teleport_coords` VALUES ('11409', 'Teleport to Booty Bay', '0', '-14319.3', '442.7', '22.94', '0');
INSERT INTO `teleport_coords` VALUES ('12520', 'Teleport from Azshara Tower', '1', '3648', '-4702', '122', '0');
INSERT INTO `teleport_coords` VALUES ('12510', 'Teleport to Azshara Tower', '1', '3778', '-4611', '228', '0');
INSERT INTO `teleport_coords` VALUES ('12885', 'Teleport to Razelikh', '0', '-11235', '-2834', '158', '0');
INSERT INTO `teleport_coords` VALUES ('13044', 'Teleport to Ground', '0', '-11072', '-2859', '11', '0');
INSERT INTO `teleport_coords` VALUES ('13142', 'Teleport to Razelikh', '0', '-11235', '-2834', '158', '0');
INSERT INTO `teleport_coords` VALUES ('18960', 'Teleport: Moonglade', '1', '7979', '-2500', '489', '0');
INSERT INTO `teleport_coords` VALUES ('32272', 'Silvermoon', '530', '9473.03', '-7279.67', '14.2285', '0');
INSERT INTO `teleport_coords` VALUES ('32270', 'Silvermoon', '530', '9473.03', '-7279.67', '14.2285', '0');
INSERT INTO `teleport_coords` VALUES ('32271', 'Exodar', '530', '-3987.29', '-11846.6', '-2.01903', '0');
INSERT INTO `teleport_coords` VALUES ('32268', 'Exodar', '530', '-3987.29', '-11846.6', '-2.01903', '0');
INSERT INTO `teleport_coords` VALUES ('35715', 'Shattrath', '530', '-1863.03', '4998.05', '-21.1847', '0');
INSERT INTO `teleport_coords` VALUES ('35718', 'Shattrath', '530', '-1863.03', '4998.05', '-21.1847', '0');
INSERT INTO `teleport_coords` VALUES ('33728', 'Shattrath', '530', '-1863.03', '4998.05', '-21.1847', '0');

-- ----------------------------
-- Table structure for `totemspells`
-- ----------------------------
DROP TABLE IF EXISTS `totemspells`;
CREATE TABLE `totemspells` (
  `spellId` int(30) NOT NULL DEFAULT '0',
  `spellToCast1` int(30) NOT NULL DEFAULT '0',
  `spellToCast2` int(30) NOT NULL DEFAULT '0',
  `spellToCast3` int(30) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of totemspells
-- ----------------------------
INSERT INTO `totemspells` VALUES ('1535', '8443', '0', '0');
INSERT INTO `totemspells` VALUES ('2484', '3600', '0', '0');
INSERT INTO `totemspells` VALUES ('3599', '3606', '0', '0');
INSERT INTO `totemspells` VALUES ('5394', '5672', '0', '0');
INSERT INTO `totemspells` VALUES ('5675', '5677', '0', '0');
INSERT INTO `totemspells` VALUES ('5730', '5728', '0', '0');
INSERT INTO `totemspells` VALUES ('6363', '6350', '0', '0');
INSERT INTO `totemspells` VALUES ('6364', '6351', '0', '0');
INSERT INTO `totemspells` VALUES ('6365', '6352', '0', '0');
INSERT INTO `totemspells` VALUES ('6375', '6371', '0', '0');
INSERT INTO `totemspells` VALUES ('6377', '6372', '0', '0');
INSERT INTO `totemspells` VALUES ('6390', '6397', '0', '0');
INSERT INTO `totemspells` VALUES ('6391', '6398', '0', '0');
INSERT INTO `totemspells` VALUES ('6392', '6399', '0', '0');
INSERT INTO `totemspells` VALUES ('6495', '0', '0', '0');
INSERT INTO `totemspells` VALUES ('8071', '8072', '0', '0');
INSERT INTO `totemspells` VALUES ('8075', '8076', '0', '0');
INSERT INTO `totemspells` VALUES ('8143', '8146', '0', '0');
INSERT INTO `totemspells` VALUES ('8154', '8156', '0', '0');
INSERT INTO `totemspells` VALUES ('8155', '8157', '0', '0');
INSERT INTO `totemspells` VALUES ('8160', '8162', '0', '0');
INSERT INTO `totemspells` VALUES ('8161', '8163', '0', '0');
INSERT INTO `totemspells` VALUES ('8166', '8167', '0', '0');
INSERT INTO `totemspells` VALUES ('8170', '8172', '0', '0');
INSERT INTO `totemspells` VALUES ('8177', '8179', '0', '0');
INSERT INTO `totemspells` VALUES ('8181', '8182', '0', '0');
INSERT INTO `totemspells` VALUES ('8184', '8185', '0', '0');
INSERT INTO `totemspells` VALUES ('8190', '8188', '0', '0');
INSERT INTO `totemspells` VALUES ('8227', '8230', '0', '0');
INSERT INTO `totemspells` VALUES ('8249', '8250', '0', '0');
INSERT INTO `totemspells` VALUES ('8262', '0', '0', '0');
INSERT INTO `totemspells` VALUES ('8264', '8266', '0', '0');
INSERT INTO `totemspells` VALUES ('8376', '8378', '0', '0');
INSERT INTO `totemspells` VALUES ('8498', '8504', '0', '0');
INSERT INTO `totemspells` VALUES ('8499', '8505', '0', '0');
INSERT INTO `totemspells` VALUES ('8512', '8514', '0', '0');
INSERT INTO `totemspells` VALUES ('8835', '8836', '0', '0');
INSERT INTO `totemspells` VALUES ('10406', '10403', '0', '0');
INSERT INTO `totemspells` VALUES ('10407', '10404', '0', '0');
INSERT INTO `totemspells` VALUES ('10408', '10405', '0', '0');
INSERT INTO `totemspells` VALUES ('10427', '10425', '0', '0');
INSERT INTO `totemspells` VALUES ('10428', '10426', '0', '0');
INSERT INTO `totemspells` VALUES ('10437', '10435', '0', '0');
INSERT INTO `totemspells` VALUES ('10438', '10436', '0', '0');
INSERT INTO `totemspells` VALUES ('10442', '10441', '0', '0');
INSERT INTO `totemspells` VALUES ('10462', '10460', '0', '0');
INSERT INTO `totemspells` VALUES ('10463', '10461', '0', '0');
INSERT INTO `totemspells` VALUES ('10478', '10476', '0', '0');
INSERT INTO `totemspells` VALUES ('10479', '10477', '0', '0');
INSERT INTO `totemspells` VALUES ('10495', '10491', '0', '0');
INSERT INTO `totemspells` VALUES ('10496', '10493', '0', '0');
INSERT INTO `totemspells` VALUES ('10497', '10494', '0', '0');
INSERT INTO `totemspells` VALUES ('10526', '10521', '0', '0');
INSERT INTO `totemspells` VALUES ('10537', '10534', '0', '0');
INSERT INTO `totemspells` VALUES ('10538', '10535', '0', '0');
INSERT INTO `totemspells` VALUES ('10585', '10582', '0', '0');
INSERT INTO `totemspells` VALUES ('10586', '10583', '0', '0');
INSERT INTO `totemspells` VALUES ('10587', '10584', '0', '0');
INSERT INTO `totemspells` VALUES ('10595', '10596', '0', '0');
INSERT INTO `totemspells` VALUES ('10600', '10598', '0', '0');
INSERT INTO `totemspells` VALUES ('10601', '10599', '0', '0');
INSERT INTO `totemspells` VALUES ('10613', '10607', '0', '0');
INSERT INTO `totemspells` VALUES ('10614', '10611', '0', '0');
INSERT INTO `totemspells` VALUES ('10627', '10626', '0', '0');
INSERT INTO `totemspells` VALUES ('11314', '11310', '0', '0');
INSERT INTO `totemspells` VALUES ('11315', '11311', '0', '0');
INSERT INTO `totemspells` VALUES ('12506', '12504', '0', '0');
INSERT INTO `totemspells` VALUES ('15038', '0', '0', '0');
INSERT INTO `totemspells` VALUES ('15107', '15108', '0', '0');
INSERT INTO `totemspells` VALUES ('15111', '15109', '0', '0');
INSERT INTO `totemspells` VALUES ('15112', '15110', '0', '0');
INSERT INTO `totemspells` VALUES ('15786', '3600', '0', '0');
INSERT INTO `totemspells` VALUES ('15787', '15789', '0', '0');
INSERT INTO `totemspells` VALUES ('15867', '0', '0', '0');
INSERT INTO `totemspells` VALUES ('16190', '16191', '0', '0');
INSERT INTO `totemspells` VALUES ('16387', '15036', '0', '0');
INSERT INTO `totemspells` VALUES ('17354', '17355', '0', '0');
INSERT INTO `totemspells` VALUES ('17359', '17360', '0', '0');
INSERT INTO `totemspells` VALUES ('18975', '18978', '0', '0');
INSERT INTO `totemspells` VALUES ('22047', '0', '0', '0');
INSERT INTO `totemspells` VALUES ('23419', '11311', '0', '0');
INSERT INTO `totemspells` VALUES ('23420', '10405', '0', '0');
INSERT INTO `totemspells` VALUES ('23422', '10461', '0', '0');
INSERT INTO `totemspells` VALUES ('23423', '10611', '0', '0');
INSERT INTO `totemspells` VALUES ('25359', '25360', '0', '0');
INSERT INTO `totemspells` VALUES ('25361', '25362', '0', '0');
INSERT INTO `totemspells` VALUES ('25908', '25909', '0', '0');
INSERT INTO `totemspells` VALUES ('27621', '10611', '0', '0');
INSERT INTO `totemspells` VALUES ('27623', '11311', '0', '0');
INSERT INTO `totemspells` VALUES ('25508', '25506', '0', '0');
INSERT INTO `totemspells` VALUES ('25509', '25507', '0', '0');
INSERT INTO `totemspells` VALUES ('25577', '25576', '0', '0');
INSERT INTO `totemspells` VALUES ('25546', '25538', '0', '0');
INSERT INTO `totemspells` VALUES ('25547', '25539', '0', '0');
INSERT INTO `totemspells` VALUES ('25533', '25530', '0', '0');
INSERT INTO `totemspells` VALUES ('8187', '8188', '0', '0');
INSERT INTO `totemspells` VALUES ('25552', '25551', '0', '0');
INSERT INTO `totemspells` VALUES ('25525', '25513', '0', '0');
INSERT INTO `totemspells` VALUES ('25555', '25554', '0', '0');
INSERT INTO `totemspells` VALUES ('25528', '25527', '0', '0');
INSERT INTO `totemspells` VALUES ('25587', '25582', '0', '0');
INSERT INTO `totemspells` VALUES ('3738', '2895', '0', '0');
INSERT INTO `totemspells` VALUES ('25567', '25566', '0', '0');
INSERT INTO `totemspells` VALUES ('25570', '25569', '0', '0');
INSERT INTO `totemspells` VALUES ('25574', '25573', '0', '0');
INSERT INTO `totemspells` VALUES ('25560', '25559', '0', '0');
INSERT INTO `totemspells` VALUES ('25563', '25562', '0', '0');
INSERT INTO `totemspells` VALUES ('30706', '30708', '0', '0');

-- ----------------------------
-- Table structure for `trainers`
-- ----------------------------
DROP TABLE IF EXISTS `trainers`;
CREATE TABLE `trainers` (
  `creature_id` int(11) NOT NULL DEFAULT '0',
  `SkillLine1` int(11) NOT NULL DEFAULT '0',
  `SkillLine2` int(11) NOT NULL DEFAULT '0',
  `SkillLine3` int(11) NOT NULL DEFAULT '0',
  `SkillLine4` int(11) NOT NULL DEFAULT '0',
  `SkillLine5` int(11) NOT NULL DEFAULT '0',
  `SkillLine6` int(11) NOT NULL DEFAULT '0',
  `SkillLine7` int(11) NOT NULL DEFAULT '0',
  `SkillLine8` int(11) NOT NULL DEFAULT '0',
  `SkillLine9` int(11) NOT NULL DEFAULT '0',
  `SkillLine10` int(11) NOT NULL DEFAULT '0',
  `SkillLine11` int(11) NOT NULL DEFAULT '0',
  `SkillLine12` int(11) NOT NULL DEFAULT '0',
  `SkillLine13` int(11) NOT NULL DEFAULT '0',
  `SkillLine14` int(11) NOT NULL DEFAULT '0',
  `SkillLine15` int(11) NOT NULL DEFAULT '0',
  `SkillLine16` int(11) NOT NULL DEFAULT '0',
  `SkillLine17` int(11) NOT NULL DEFAULT '0',
  `SkillLine18` int(11) NOT NULL DEFAULT '0',
  `SkillLine19` int(11) NOT NULL DEFAULT '0',
  `SkillLine20` int(11) NOT NULL DEFAULT '0',
  `MaxLvL` int(11) NOT NULL DEFAULT '0',
  `Class` int(11) DEFAULT NULL,
  `TalkText` varchar(150) NOT NULL DEFAULT ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of trainers
-- ----------------------------

-- ----------------------------
-- Table structure for `trainerspelloverride`
-- ----------------------------
DROP TABLE IF EXISTS `trainerspelloverride`;
CREATE TABLE `trainerspelloverride` (
  `spellid` int(10) unsigned NOT NULL DEFAULT '0',
  `cost` int(10) unsigned NOT NULL DEFAULT '0',
  `requiredspell` int(10) unsigned NOT NULL DEFAULT '0',
  `deletespell` int(10) unsigned NOT NULL DEFAULT '0',
  `requiredskill` int(10) unsigned NOT NULL DEFAULT '0',
  `requiredskillvalue` int(10) unsigned NOT NULL DEFAULT '0',
  `reqlevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `requiredclass` int(10) NOT NULL DEFAULT '-1',
  UNIQUE KEY `spellid` (`spellid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of trainerspelloverride
-- ----------------------------

-- ----------------------------
-- Table structure for `transport_data`
-- ----------------------------
DROP TABLE IF EXISTS `transport_data`;
CREATE TABLE `transport_data` (
  `entry` int(11) unsigned NOT NULL DEFAULT '0',
  `name` text,
  `period` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of transport_data
-- ----------------------------
INSERT INTO `transport_data` VALUES ('20808', 'Ratchet and Booty Bay', '350818');
INSERT INTO `transport_data` VALUES ('164871', 'Orgrimmar and Undercity', '356284');
INSERT INTO `transport_data` VALUES ('175080', 'Grom\'Gol Base Camp and Orgrimmar', '303463');
INSERT INTO `transport_data` VALUES ('176231', 'Menethil Harbor and Theramore Isle', '329313');
INSERT INTO `transport_data` VALUES ('176244', 'Teldrassil and Auberdine', '325171');
INSERT INTO `transport_data` VALUES ('176310', 'Menethil Harbor and Auberdine', '295680');
INSERT INTO `transport_data` VALUES ('176495', 'Grom\'Gol Base Camp and Undercity', '333044');
INSERT INTO `transport_data` VALUES ('177233', 'Forgotton Coast and Feathermoon Stronghold', '317038');
INSERT INTO `transport_data` VALUES ('181646', 'Exodar Ship', '259920');

-- ----------------------------
-- Table structure for `tutorials`
-- ----------------------------
DROP TABLE IF EXISTS `tutorials`;
CREATE TABLE `tutorials` (
  `playerId` int(20) unsigned NOT NULL DEFAULT '0',
  `tut0` int(20) unsigned NOT NULL DEFAULT '0',
  `tut1` int(20) unsigned NOT NULL DEFAULT '0',
  `tut2` int(20) unsigned NOT NULL DEFAULT '0',
  `tut3` int(20) unsigned NOT NULL DEFAULT '0',
  `tut4` int(20) unsigned NOT NULL DEFAULT '0',
  `tut5` int(20) unsigned NOT NULL DEFAULT '0',
  `tut6` int(20) unsigned NOT NULL DEFAULT '0',
  `tut7` int(20) unsigned NOT NULL DEFAULT '0',
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5106699 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of tutorials
-- ----------------------------

-- ----------------------------
-- Table structure for `vendors`
-- ----------------------------
DROP TABLE IF EXISTS `vendors`;
CREATE TABLE `vendors` (
  `vendorGuid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `itemGuid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `amount` bigint(20) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of vendors
-- ----------------------------

-- ----------------------------
-- Table structure for `weather`
-- ----------------------------
DROP TABLE IF EXISTS `weather`;
CREATE TABLE `weather` (
  `zoneId` bigint(20) unsigned NOT NULL DEFAULT '0',
  `effect_none` bigint(20) unsigned NOT NULL DEFAULT '0',
  `effect_rain` bigint(20) unsigned NOT NULL DEFAULT '0',
  `effect_snow` bigint(20) unsigned NOT NULL DEFAULT '0',
  `effect_weak_rain` bigint(20) unsigned NOT NULL DEFAULT '0',
  `effect_unk` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`zoneId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of weather
-- ----------------------------

-- ----------------------------
-- Table structure for `worldmap_info`
-- ----------------------------
DROP TABLE IF EXISTS `worldmap_info`;
CREATE TABLE `worldmap_info` (
  `mapid` int(10) NOT NULL DEFAULT '0',
  `screenid` int(10) DEFAULT '0',
  `type` int(10) DEFAULT '0',
  `maxplayers` int(10) DEFAULT '0',
  `minlevel` int(11) unsigned zerofill DEFAULT '00000000001',
  `repopx` float DEFAULT '0',
  `repopy` float DEFAULT '0',
  `repopz` float DEFAULT '0',
  `repopmapid` int(5) unsigned zerofill DEFAULT '00000',
  `area_name` varchar(100) DEFAULT '0',
  `flags` int(11) unsigned NOT NULL DEFAULT '0',
  `cooldown` int(15) NOT NULL DEFAULT '0',
  `lvl_mod_a` int(10) unsigned NOT NULL DEFAULT '0',
  `required_quest` int(5) unsigned NOT NULL DEFAULT '0',
  `required_item` int(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`mapid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of worldmap_info
-- ----------------------------
INSERT INTO `worldmap_info` VALUES ('0', '0', '0', '0', '00000000001', '0', '0', '0', '00000', 'Estern Kingdoms Continent', '1', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('1', '1', '0', '0', '00000000001', '0', '0', '0', '00001', 'Kalimdor Continent', '1', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('30', '30', '3', '0', '00000000001', '0', '0', '0', '00000', 'Alterac Valley', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('33', '204', '2', '5', '00000000001', '-229.49', '1576.35', '78.8909', '00000', 'Shadowfang Keep', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('34', '34', '2', '5', '00000000001', '-8769.86', '842.181', '89.8765', '00000', 'Stormwind Stockades', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('35', '194', '2', '5', '00000000001', '0', '0', '0', '00000', 'Stormwind Vault - UNUSED', '0', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('36', '36', '2', '5', '00000000008', '-11208.4', '1673.85', '24.6245', '00000', 'DeadMines', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('43', '143', '2', '5', '00000000008', '-753.596', '-2212.78', '21.5403', '00001', 'Wailing Caverns', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('47', '188', '2', '5', '00000000001', '-4456.7', '-1655.99', '86.1095', '00001', 'Razorfen Kraul', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('48', '196', '2', '5', '00000000008', '4252.37', '756.974', '-23.0632', '00001', 'Blackfathom Deeps', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('70', '144', '2', '5', '00000000001', '-6606.48', '-3762.19', '266.91', '00000', 'Uldaman', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('90', '193', '2', '5', '00000000001', '-5081.82', '719.549', '260.554', '00000', 'Gnomeregan', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('109', '109', '2', '5', '00000000001', '-10184.9', '-3992.84', '-109.194', '00000', 'Temple of Atal\'Hakkar', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('129', '145', '2', '5', '00000000001', '-4666.52', '-2536.82', '86.9671', '00001', 'Razorfen Downs', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('189', '42', '2', '5', '00000000008', '2870.97', '-759.845', '160.333', '00000', 'Scarlet Monastery', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('209', '146', '2', '5', '00000000001', '-6773.49', '-2889.77', '15.1063', '00001', 'Zul\'Farrak', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('229', '189', '2', '10', '00000000055', '-7518.19', '-1239.13', '287.243', '00000', 'Blackrock Spire', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('230', '103', '2', '10', '00000000055', '-7176.63', '-937.667', '170.206', '00000', 'Blackrock Depths', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('249', '61', '1', '40', '00000000055', '-4768.61', '-3752.11', '53.4317', '00001', 'Onyxia\'s Lair', '3', '432000', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('269', '269', '4', '5', '00000000064', '-8770.08', '-4171.7', '-210.158', '00001', 'Opening of the Dark Portal', '15', '54000', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('289', '102', '2', '5', '00000000055', '1282.05', '-2548.73', '85.3994', '00000', 'Scholomance', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('309', '161', '1', '20', '00000000055', '-11915.8', '-1236.43', '96.1502', '00000', 'Zul\'Gurub', '3', '259200', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('329', '101', '2', '5', '00000000055', '3237.46', '-4060.6', '112.01', '00000', 'Stratholme', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('349', '81', '2', '5', '00000000001', '-1431.07', '2970.64', '99.8095', '00000', 'Maraudon', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('369', '369', '0', '0', '00000000001', '0', '0', '0', '00000', 'Deeprun Tram', '1', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('389', '195', '2', '5', '00000000008', '1818.4', '-4427.26', '-10.4478', '00001', 'Ragefire Chasm', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('409', '192', '1', '40', '00000000055', '-7510.31', '-1041.63', '180.912', '00000', 'Molten Core', '3', '604800', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('429', '82', '2', '5', '00000000001', '-4278.76', '1332.49', '161.214', '00001', 'Dire Maul', '3', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('449', '181', '0', '0', '00000000001', '-8761.85', '848.557', '87.8052', '00000', 'Alliance Military Barracks', '1', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('450', '182', '0', '0', '00000000001', '1643.36', '-4233.6', '56.1557', '00001', 'Horde Military Barracks', '1', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('469', '141', '1', '40', '00000000055', '-7655.63', '-1221.93', '287.798', '00000', 'Blackwing Lair', '3', '604800', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('509', '184', '1', '20', '00000000055', '-8134.79', '1525.9', '6.1904', '00001', 'Ahn\'Qiraj Ruins', '0', '259200', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('530', '530', '0', '0', '00000000055', '0', '0', '0', '00530', 'Outlands', '9', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('531', '531', '1', '40', '00000000055', '-8134.79', '1525.9', '6.1904', '00001', 'Ahn\'Qiraj Temple', '0', '259200', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('532', '532', '2', '10', '00000000068', '0', '0', '0', '00000', 'Karazahn', '9', '0', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('533', '0', '1', '40', '00000000055', '3237.46', '-4060.6', '112.01', '00000', 'Naxxramas', '0', '604800', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('534', '534', '1', '25', '00000000068', '-8178.25', '-4184.74', '-168.4', '00001', 'The Battle for Mount Hyjal', '9', '604800', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('545', '545', '4', '5', '00000000064', '816.87', '6935.02', '-80.5606', '00530', 'The Steamvault', '15', '54000', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('553', '553', '4', '5', '00000000064', '3365.84', '1519.15', '179.541', '00530', 'The Botanica', '15', '54000', '0', '0', '0');
INSERT INTO `worldmap_info` VALUES ('560', '560', '4', '5', '00000000064', '-8343.69', '-4057.43', '207.924', '00001', 'Caverns Of Time - Old Hillsbrad Foothills', '15', '54000', '0', '0', '0');
