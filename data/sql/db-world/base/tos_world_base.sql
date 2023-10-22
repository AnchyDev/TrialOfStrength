DELETE FROM `instance_template` WHERE `map`=44;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES (44, 0, 'instance_trial_of_strength', 0);


-- Combatant / Melee
DELETE FROM `creature_template` WHERE `entry`=441251;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (441251, 0, 0, 0, 0, 0, 3960, 4443, 4021, 4024, 'Enemy Combatant', 'Melee', NULL, 0, 80, 80, 0, 17, 0, 1, 1.14286, 1, 1, 20, 1, 0, 0, 5, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'CombatAI', 0, 1, 2, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'ToSEnemyCombatantScript', 1);

DELETE FROM `creature_equip_template` WHERE `CreatureID`=441251 AND `ID`=1;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`, `VerifiedBuild`) VALUES (441251, 1, 1899, 2052, 0, NULL);


-- Combatant / Melee Boss
DELETE FROM `creature_template` WHERE `entry`=441252;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (441252, 0, 0, 0, 0, 0, 3960, 4443, 4021, 4024, 'Enemy Combatant', 'Boss', NULL, 0, 80, 80, 0, 17, 0, 1, 1.14286, 1, 1, 20, 1.5, 3, 0, 5, 2000, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'CombatAI', 0, 1, 6, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'ToSEnemyCombatantBossScript', 1);

DELETE FROM `creature_equip_template` WHERE `CreatureID`=441252 AND `ID`=1;
INSERT INTO `creature_equip_template` (`CreatureID`, `ID`, `ItemID1`, `ItemID2`, `ItemID3`, `VerifiedBuild`) VALUES (441252, 1, 1899, 2052, 0, NULL);


-- Trial of Strength / Arena Master
DELETE FROM `creature_template` WHERE `entry`=441250;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (441250, 0, 0, 0, 0, 0, 18039, 0, 0, 0, 'Fortichad Ironfist', 'Arena Master', NULL, 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 1, 20, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'ToSArenaMasterScript', 1);

-- Trial of Strength / Arena Spectator
DELETE FROM `creature_template` WHERE `entry`=441253;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `speed_swim`, `speed_flight`, `detection_range`, `scale`, `rank`, `dmgschool`, `DamageModifier`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (441253, 0, 0, 0, 0, 0, 1485, 3606, 4123, 2224, 'Arena Spectator', NULL, NULL, 0, 78, 80, 0, 35, 0, 1, 1.14286, 1, 1, 20, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'ToSArenaSpectatorScript', 1);


DELETE FROM `npc_text` WHERE `ID`=441250;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES (441250, 'Greetings, $n.|n|nI am the Arena Master for the Trial of Strength.|n|nIf you seek to test your abilities, then I can transport you to the arena.|n|nAre you ready to face the challenges that lie ahead?', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
DELETE FROM `npc_text` WHERE `ID`=441251;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES (441251, 'Welcome $n, are you ready to start the Trial of Strength?', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
DELETE FROM `npc_text` WHERE `ID`=441252;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES (441252, 'You must finish the current trial before speaking to me again.', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
DELETE FROM `npc_text` WHERE `ID`=441253;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES (441253, 'Are you ready for the next trial?', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
DELETE FROM `npc_text` WHERE `ID`=441254;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `Probability0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `Probability1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `Probability2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `Probability3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `Probability4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `Probability5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `Probability6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `Probability7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES (441254, 'Congratulations, $n!|n|nYou have triumphed in the Trial of Strength, proving your mettle and determination. Your strength and skill have shone brightly, and your name will be celebrated in the annals of our arena\'s history.|n|nWhat would you like to do now?', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL);

DELETE FROM `gameobject_template` WHERE `entry`=441250;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES (441250, 3, 259, 'Arena Master\'s Lootbox', '', '', '', 1.25, 57, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 1);

DELETE FROM `gameobject_template` WHERE `entry`=441251;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES (441251, 5, 3272, 'Arena Master\'s Lootbox Beam', '', '', '', 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 1);

DELETE FROM `gameobject_template` WHERE `entry`=441252;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES (441252, 2, 327, 'Curse Crystal', '', '', '', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'ToSCurseCrystalScript', 1);

DELETE FROM `gameobject_template` WHERE `entry`=441352;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES (441352, 5, 7148, 'ToSArenaPortal', '', '', '', 0.85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', NULL);


CREATE TABLE IF NOT EXISTS `tos_reward_template` (
  `id` int DEFAULT NULL,
  `item_entry` int DEFAULT NULL,
  `count_min` int DEFAULT NULL,
  `count_max` int DEFAULT NULL,
  `chance` float DEFAULT NULL,
  `note` varchar(50) COLLATE utf8mb4_general_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tos_wave_groups` (
  `id` int DEFAULT NULL,
  `group` int DEFAULT NULL,
  `sub_group` int DEFAULT NULL,
  `creature` int DEFAULT NULL,
  `note` varchar(50) COLLATE utf8mb4_general_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tos_wave_template` (
  `wave` int DEFAULT NULL,
  `enemy_group` int DEFAULT NULL,
  `has_reward` tinyint DEFAULT NULL,
  `reward_template` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tos_curse_template` (
  `id` int DEFAULT NULL,
  `type` int DEFAULT NULL,
  `difficulty` int DEFAULT NULL,
  `aura` int DEFAULT NULL,
  `name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  `description` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

DELETE FROM `tos_curse_template` WHERE `id`=1 AND `type`=0 AND `difficulty`=50 AND `aura`=68335 AND `name`='Enrage' AND `description`='Combatants are enraged, increasing their damage by 50%.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (1, 0, 50, 68335, 'Enrage', 'Combatants are enraged, increasing their damage by 50%.');
DELETE FROM `tos_curse_template` WHERE `id`=15 AND `type`=0 AND `difficulty`=60 AND `aura`=71110 AND `name`='Aura of Darkness' AND `description`='Combatants are consumed by darkness, radiating shadow damage every 2 seconds.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (15, 0, 60, 71110, 'Aura of Darkness', 'Combatants are consumed by darkness, radiating shadow damage every 2 seconds.');
DELETE FROM `tos_curse_template` WHERE `id`=16 AND `type`=0 AND `difficulty`=50 AND `aura`=25820 AND `name`='Fearful' AND `description`='Combatants have a 10% chance when taking damage to fear players.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (16, 0, 50, 25820, 'Fearful', 'Combatants have a 10% chance when taking damage to fear players.');
DELETE FROM `tos_curse_template` WHERE `id`=5 AND `type`=0 AND `difficulty`=0 AND `aura`=45673 AND `name`='Bigger!' AND `description`='Combatants are 15-25 percent larger!';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (5, 0, 0, 45673, 'Bigger!', 'Combatants are 15-25 percent larger!');
DELETE FROM `tos_curse_template` WHERE `id`=6 AND `type`=0 AND `difficulty`=20 AND `aura`=45444 AND `name`='Hot Hands' AND `description`='Combatants have bonfire\'s blessing, infusing their attacks with flame.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (6, 0, 20, 45444, 'Hot Hands', 'Combatants have bonfire\'s blessing, infusing their attacks with flame.');
DELETE FROM `tos_curse_template` WHERE `id`=18 AND `type`=1 AND `difficulty`=60 AND `aura`=35500 AND `name`='Dampened' AND `description`='Players have 50% reduced maximum health and 50% increased mana cost of spells.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (18, 1, 60, 35500, 'Dampened', 'Players have 50% reduced maximum health and 50% increased mana cost of spells.');
DELETE FROM `tos_curse_template` WHERE `id`=19 AND `type`=0 AND `difficulty`=60 AND `aura`=31317 AND `name`='Vampiric' AND `description`='Combatants melee attacks heal for 300% of the damage.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (19, 0, 60, 31317, 'Vampiric', 'Combatants melee attacks heal for 300% of the damage.');
DELETE FROM `tos_curse_template` WHERE `id`=7 AND `type`=1 AND `difficulty`=50 AND `aura`=69127 AND `name`='Chill of the Throne' AND `description`='Players have a 20% reduced chance to dodge.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (7, 1, 50, 69127, 'Chill of the Throne', 'Players have a 20% reduced chance to dodge.');
DELETE FROM `tos_curse_template` WHERE `id`=8 AND `type`=1 AND `difficulty`=10 AND `aura`=41631 AND `name`='Cold Feet' AND `description`='Players have a 20% reduced movement speed.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (8, 1, 10, 41631, 'Cold Feet', 'Players have a 20% reduced movement speed.');
DELETE FROM `tos_curse_template` WHERE `id`=9 AND `type`=0 AND `difficulty`=10 AND `aura`=41630 AND `name`='Hot Feet' AND `description`='Combatants have a 30% increased movement speed.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (9, 0, 10, 41630, 'Hot Feet', 'Combatants have a 30% increased movement speed.');
DELETE FROM `tos_curse_template` WHERE `id`=10 AND `type`=0 AND `difficulty`=50 AND `aura`=64193 AND `name`='Heart Broken' AND `description`='Combatants have 15% increased damage and 60% increased health.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (10, 0, 50, 64193, 'Heart Broken', 'Combatants have 15% increased damage and 60% increased health.');
DELETE FROM `tos_curse_template` WHERE `id`=11 AND `type`=1 AND `difficulty`=0 AND `aura`=45672 AND `name`='Shorter!' AND `description`='Players are 45-75 percent smaller!';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (11, 1, 0, 45672, 'Shorter!', 'Players are 45-75 percent smaller!');
DELETE FROM `tos_curse_template` WHERE `id`=12 AND `type`=0 AND `difficulty`=20 AND `aura`=33795 AND `name`='Strength of Halaa' AND `description`='Combatants have 5% increased damage.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (12, 0, 20, 33795, 'Strength of Halaa', 'Combatants have 5% increased damage.');
DELETE FROM `tos_curse_template` WHERE `id`=17 AND `type`=0 AND `difficulty`=30 AND `aura`=39444 AND `name`='Vengeance' AND `description`='Combatants have a 10% chance when taking damage to deal holy damage to the player.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (17, 0, 30, 39444, 'Vengeance', 'Combatants have a 10% chance when taking damage to deal holy damage to the player.');
DELETE FROM `tos_curse_template` WHERE `id`=13 AND `type`=0 AND `difficulty`=100 AND `aura`=58361 AND `name`='Might of Mograine' AND `description`='Combatants have 500% increased damage, 15000% increased health and 25% of health is regenerated every 2 seconds.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (13, 0, 100, 58361, 'Might of Mograine', 'Combatants have 500% increased damage, 15000% increased health and 25% of health is regenerated every 2 seconds.');
DELETE FROM `tos_curse_template` WHERE `id`=14 AND `type`=0 AND `difficulty`=20 AND `aura`=33779 AND `name`='Twin Spire Blessing' AND `description`='Combatants have 5% increased damage.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (14, 0, 20, 33779, 'Twin Spire Blessing', 'Combatants have 5% increased damage.');
DELETE FROM `tos_curse_template` WHERE `id`=2 AND `type`=0 AND `difficulty`=100 AND `aura`=29476 AND `name`='Astral Armor' AND `description`='Combatants are protected, decreasing the damage they receive by 90%.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (2, 0, 100, 29476, 'Astral Armor', 'Combatants are protected, decreasing the damage they receive by 90%.');
DELETE FROM `tos_curse_template` WHERE `id`=3 AND `type`=1 AND `difficulty`=60 AND `aura`=34102 AND `name`='Curse of the Violet Tower' AND `description`='Players are weakened, dealing 50% less damage.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (3, 1, 60, 34102, 'Curse of the Violet Tower', 'Players are weakened, dealing 50% less damage.');
DELETE FROM `tos_curse_template` WHERE `id`=4 AND `type`=0 AND `difficulty`=75 AND `aura`=34337 AND `name`='Armored Skin' AND `description`='Combatants skin have been strengthened, taking 75% less physical damage.';
INSERT INTO `tos_curse_template` (`id`, `type`, `difficulty`, `aura`, `name`, `description`) VALUES (4, 0, 75, 34337, 'Armored Skin', 'Combatants skin have been strengthened, taking 75% less physical damage.');
