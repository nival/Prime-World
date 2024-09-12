DROP TABLE IF EXISTS `tbl_admin_messages`;
CREATE TABLE  `tbl_admin_messages` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(32) NOT NULL COMMENT 'social requisites, "<snid>#<snuid>" form',
  `instance_id` int(10) unsigned NOT NULL COMMENT 'message id in ModelData Keeper',
  `title` VARCHAR(128) COMMENT 'message title',
  `message` VARCHAR(2048) NOT NULL COMMENT 'message text',
  `gmlogin` varchar(32) NOT NULL COMMENT 'gmAccount that added this message',
  `viewed` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'was viewed by user',
  `timestamp` int(10) DEFAULT 0 COMMENT 'creation unixtime',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;