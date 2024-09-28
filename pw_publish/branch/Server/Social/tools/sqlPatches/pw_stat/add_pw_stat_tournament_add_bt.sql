ALTER TABLE  `pw_stat`.`tournaments` ADD COLUMN
`bought_type` tinyint unsigned NOT NULL DEFAULT 0 COMMENT 'code, saying how the ticket was bought'
AFTER `timestamp`;