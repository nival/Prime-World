-- Move current rating and place values to prev_
-- ... Remember to make backup of `pw_stat`.`tbl_guild_rating` first
USE `pw_stat`;
SET SQL_SAFE_UPDATES = OFF; -- < MAKE BACKUP FIRST!!!
UPDATE `tbl_guild_rating` SET
    `prev_rating` = `rating`,
    `prev_place` = `position`;
UPDATE `tbl_guild_rating` SET
    `rating` = 0,
    `position` = 1000000000,
    `position_change` = 0;
