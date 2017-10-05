DROP TABLE IF EXISTS [Settings];
CREATE TABLE [Settings]([rowid] INTEGER, [ID] INTEGER, [Setting_Key] VARCHAR, [Setting_Value] VARCHAR, [Description] VARCHAR, [Setting_Area] VARCHAR);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(1, 1, 'P_Weapon_Shd_Dmg_Multi_Easy', '2', 'Difficulty: Easy
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 2.0 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(2, 2, 'P_Weapon_Arm_Dmg_Multi_Easy', '1.5', 'Difficulty: Easy
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 1.5 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(3, 3, 'P_Weapon_Hull_Dmg_Multi_Easy', '1.25', 'Difficulty: Easy
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 1.25 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(4, 4, 'P_Weapon_Shd_Dmg_Multi_Moderate', '1', 'Difficulty: Moderate
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 1 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(5, 5, 'P_Weapon_Arm_Dmg_Multi_Moderate', '1', 'Difficulty: Moderate
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 1 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(6, 6, 'P_Weapon_Hull_Dmg_Multi_Moderate', '1', 'Difficulty: Moderate
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 1 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(7, 7, 'P_Weapon_Shd_Dmg_Multi_Hard', '1', 'Difficulty: Hard
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.75 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(8, 8, 'P_Weapon_Arm_Dmg_Multi_Hard', '0.75', 'Difficulty: Hard
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 0.75 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(9, 9, 'P_Weapon_Hull_Dmg_Multi_Hard', '0.68', 'Difficulty: Hard
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 0.75 (Default)

', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(10, 10, 'P_Weapon_Shd_Dmg_Multi_Extreme', '0.755', 'Difficulty: Extreme
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.50 (Default)

', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(11, 11, 'P_Weapon_Arm_Dmg_Multi_Extreme', '0.5', 'Difficulty: Extreme
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 0.50 (Default)', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(12, 12, 'P_Weapon_Hull_Dmg_Multi_Extreme', '0.45', 'Difficulty: Extreme
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.50 (Default)', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(13, 13, 'P_Weapon_Shd_Dmg_Multi_Realistic', '0.65', 'Difficulty: Realistic
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.75 (Default)
', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(14, 14, 'P_Weapon_Arm_Dmg_Multi_Realistic', '0.35', 'Difficulty: Realistic
Setting: Outgoing Armor Damage (damage to enemy Armor)
Modifier: 1.25 (Default)
', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(15, 15, 'P_Weapon_Hull_Dmg_Multi_Realistic', '0.30', 'Difficulty: Realistic
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 2 (Default)
', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(16, 16, 'N_Weapon_Shd_Dmg_Multi_Easy', '0.45', 'Difficulty: Easy
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 2.0 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(17, 17, 'N_Weapon_Arm_Dmg_Multi_Easy', '0.65', 'Difficulty: Easy
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 1.5 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(18, 18, 'N_Weapon_Hull_Dmg_Multi_Easy', '0.5', 'Difficulty: Easy
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 1.25 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(19, 19, 'N_Weapon_Shd_Dmg_Multi_Moderate', '1', 'Difficulty: Moderate
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 1 (Default)', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(20, 20, 'N_Weapon_Arm_Dmg_Multi_Moderate', '1', 'Difficulty: Moderate
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 1 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(21, 21, 'N_Weapon_Hull_Dmg_Multi_Moderate', '1', 'Difficulty: Moderate
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 1 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(22, 22, 'N_Weapon_Shd_Dmg_Multi_Hard', '1.25', 'Difficulty: Hard
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.75 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(23, 23, 'N_Weapon_Arm_Dmg_Multi_Hard', '1.55', 'Difficulty: Hard
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 0.75 (Default)
', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(24, 24, 'N_Weapon_Hull_Dmg_Multi_Hard', '1.60', 'Difficulty: Hard
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 0.75 (Default)

', 'Damage');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(25, 25, 'N_Weapon_Shd_Dmg_Multi_Extreme', '1.5', 'Difficulty: Extreme
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.50 (Default)

', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(26, 26, 'N_Weapon_Arm_Dmg_Multi_Extreme', '1.6', 'Difficulty: Extreme
Setting: Outgoing Armor Damage (damage to enemy armor)
Modifier: 0.50 (Default)', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(27, 27, 'N_Weapon_Hull_Dmg_Multi_Extreme', '1.75', 'Difficulty: Extreme
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.50 (Default)', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(28, 28, 'N_Weapon_Shd_Dmg_Multi_Realistic', '1.85', 'Difficulty: Realistic
Setting: Outgoing Shield Damage (damage to enemy shields)
Modifier: 0.75 (Default)
', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(29, 29, 'N_Weapon_Arm_Dmg_Multi_Realistic', '1.98', 'Difficulty: Realistic
Setting: Outgoing Armor Damage (damage to enemy Armor)
Modifier: 1.25 (Default)
', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(30, 30, 'N_Weapon_Hull_Dmg_Multi_Realistic', '2', 'Difficulty: Realistic
Setting: Outgoing Hull Damage (damage to enemy hull)
Modifier: 2 (Default)
', null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(31, 31, 'Difficulties', 'Easy,Moderate,Hard,Extreme,Realistic', 'This setting defines the difficulty types for the game.  If you add a new difficulty please be sure to add settings for it.

If you change the name of one please be sure to alter ALL other difficulty related settings for that setting as the name listed here is used to determine the settings to use for that difficulty.

Please use underscores in place of spaces.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(32, 32, 'Scrap_Yield_Easy', '2.5', 'Difficulty: Easy
Setting: Scrap Yield
Modifer: 2.5 (Default)
Description:
	This setting allows you to modify the amount of scrap a player will receive from a
	wrecked ship.  Salvaged Amount of Resource * Modifer.
Example:
	Salvaged 20 Draconic, setting modifer makes this 50 Draconic.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(33, 33, 'Scrap_Yield_Moderate', '1.5', 'Difficulty: Moderate
Setting: Scrap Yield
Modifer: 1.5 (Default)
Description:
	This setting allows you to modify the amount of scrap a player will receive from a
	wrecked ship.  Salvaged Amount of Resource * Modifer.
Example:
	Salvaged 20 Draconic, setting modifer makes this 30 Draconic.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(34, 34, 'Scrap_Yield_Hard', '1', 'Difficulty: Hard
Setting: Scrap Yield
Modifer: 1 (Default)
Description:
	This setting allows you to modify the amount of scrap a player will receive from a
	wrecked ship.  Salvaged Amount of Resource * Modifer.
Example:
	Salvaged 20 Draconic, setting modifer makes this 20 Draconic.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(35, 35, 'Scrap_Yield_Extreme', '0.75', 'Difficulty: Extreme
Setting: Scrap Yield
Modifer: 0.75 (Default)
Description:
	This setting allows you to modify the amount of scrap a player will receive from a
	wrecked ship.  Salvaged Amount of Resource * Modifer.
Example:
	Salvaged 20 Draconic, setting modifer makes this 15 Draconic.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(36, 36, 'Scrap_Yield_Realistic', '0.5', 'Difficulty: Realistic
Setting: Scrap Yield
Modifer: 0.5 (Default)
Description:
	This setting allows you to modify the amount of scrap a player will receive from a
	wrecked ship.  Salvaged Amount of Resource * Modifer.
Example:
	Salvaged 20 Draconic, setting modifer makes this 10 Draconic.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(37, 37, 'Missile_Class_Types', 'Ultralite,Lite,Lite Standard,Lite Advanced,Standard,Standard Heavy,Medium,Heavy,Ultra Heavy,Titan', 'This setting defines the missile class types to be used in the game.  Please add your new types to the end of this list.  Some other settings may require changes if you modify or add a new class.  Please check the wiki for more details.', 'Weapon');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(38, 38, 'HSec_Ship_SRate_Easy', '0.25', 'Difficulty: Easy
Setting: High Sec Hostile Spawn Rate
Modifier: 0.25 (Default)
Description:
	This setting allows you to modify the number of spawned hostile ships in high sec space.

Example:
	This setting at 0.50 will spawn half as many hostile ships in high sec space.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(39, 39, 'HSec_Ship_SRate_Moderate', '1', 'Difficulty: Moderate
Setting: High Sec Hostile Spawn Rate
Modifier: 1.0 (Default)
Description:
	This setting allows you to modify the number of spawned hostile ships in high sec space.

Example:
	This setting at 0.50 will spawn half as many hostile ships in high sec space.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(40, 40, 'HSec_Ship_SRate_Hard', '1.5', 'Difficulty: Hard
Setting: High Sec Hostile Spawn Rate
Modifier: 1.5 (Default)
Description:
	This setting allows you to modify the number of spawned hostile ships in high sec space.

Example:
	This setting at 0.50 will spawn half as many hostile ships in high sec space.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(41, 41, 'HSec_Ship_SRate_Extreme', '1.75', 'Difficulty: Extreme
Setting: High Sec Hostile Spawn Rate
Modifier: 1.75 (Default)
Description:
	This setting allows you to modify the number of spawned hostile ships in high sec space.

Example:
	This setting at 0.50 will spawn half as many hostile ships in high sec space.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(42, 42, 'HSec_Ship_SRate_Realistic', '2', 'Difficulty: Realistic
Setting: High Sec Hostile Spawn Rate
Modifier: 2.0 (Default)
Description:
	This setting allows you to modify the number of spawned hostile ships in high sec space.

Example:
	This setting at 0.50 will spawn half as many hostile ships in high sec space.', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(43, 43, 'MSec_Ship_SRate_Easy', '0.45', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Mid_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(44, 44, 'MSec_Ship_SRate_Moderate', '1.2', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Mid_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(45, 45, 'MSec_Ship_SRate_Hard', '1.8', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Mid_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(46, 46, 'MSec_Ship_SRate_Extreme', '2', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Mid_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(47, 47, 'MSec_Ship_SRate_Realistic', '2.25', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Mid_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(48, 48, 'LSec_Ship_SRate_Easy', '0.5', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Low_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(49, 49, 'LSec_Ship_SRate_Moderate', '1.8', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Low_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(50, 50, 'LSec_Ship_SRate_Hard', '2', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Low_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(51, 51, 'LSec_Ship_SRate_Extreme', '2.25', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Low_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(52, 52, 'LSec_Ship_SRate_Realistic', '2.5', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Low_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(53, 53, 'NSec_Ship_SRate_Easy', '0.68', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Null_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(54, 54, 'NSec_Ship_SRate_Moderate', '1.95', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Null_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(55, 55, 'NSec_Ship_SRate_Hard', '2.35', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Null_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(56, 56, 'NSec_Ship_SRate_Extreme', '2.8', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Null_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(57, 57, 'NSec_Ship_SRate_Realistic', '3', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#Null_Sec_Hostile_Spawn_Rates', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(58, 58, 'CXP_P_BaseVal_Easy', '95', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Base_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(59, 59, 'CXP_P_BaseVal_Moderate', '98', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Base_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(60, 60, 'CXP_P_BaseVal_Hard', '102', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Base_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(61, 61, 'CXP_P_BaseVal_Extreme', '108', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Base_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(62, 62, 'CXP_P_BaseVal_Realistic', '115', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Base_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(63, 63, 'CXP_P_Factor_Easy', '2.1', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(64, 64, 'CXP_P_Factor_Moderate', '2.12', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(65, 65, 'CXP_P_Factor_Hard', '2.14', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(66, 66, 'CXP_P_Factor_Extreme', '2.17', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(67, 67, 'CXP_P_Factor_Realistic', '2.22', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Player_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(68, 68, 'CXP_E_Factor_Easy', '2.1', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Enemy_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(69, 69, 'CXP_E_Factor_Moderate', '2', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Enemy_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(70, 70, 'CXP_E_Factor_Hard', '1.95', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Enemy_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(71, 71, 'CXP_E_Factor_Extreme', '1.92', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Enemy_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(72, 72, 'CXP_E_Factor_Realistic', '1.87', 'http://www.lmpgames.com/w2/index.php?title=Setting_Descriptions#CXP_Enemy_Factor_Value', 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(73, 73, 'Logging_Level', '1', null, 'Logging');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(74, 74, 'Planet_Size_Rand_Max', '1000', null, 'Game');

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(75, 75, 'Planet_EKS_Range_Min', '1.0', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(76, 76, 'Planet_EKS_Range_Max', '5500.0', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(77, 77, 'Planet_Type_0_Range_Min', '0.0', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(78, 78, 'Planet_Type_0_Range_Max', '0.9', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(79, 79, 'Planet_Type_0_Size_Range_Min', '450', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(80, 80, 'Planet_Type_0_Size_Range_Max', '625', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(81, 81, 'Planet_Type_0_Outlier_Range_Min', '1.2', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(82, 82, 'Planet_Type_0_Outlier_Range_Max', '1.8', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(83, 83, 'Planet_Type_0_Size_Rand_Min', '1.0', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(84, 84, 'Planet_Type_0_Size_Rand_Max', '2.5', null, null);

INSERT INTO [Settings]([rowid], [ID], [Setting_Key], [Setting_Value], [Description], [Setting_Area])
VALUES(85, 85, 'Planet_Size_Rand_Min', '1', null, null);

