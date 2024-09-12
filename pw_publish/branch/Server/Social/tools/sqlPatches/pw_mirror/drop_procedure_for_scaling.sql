DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_get_requests` $$
CREATE PROCEDURE `sp_get_requests` ( adata_type SMALLINT, arequest_type SMALLINT, aservice_count SMALLINT, acount INTEGER, ahandler_id INTEGER )
BEGIN
    # workaround for "LIMIT const" usage
  SET @v_data_type = adata_type;
  SET @v_request_type = arequest_type;
    SET @v_service_count = aservice_count;
  SET @v_handler_id = ahandler_id;
  SET @v_count = acount;
  SET @v_timestamp = UNIX_TIMESTAMP();
  SET @v_query = 'UPDATE tbl_queue
    SET handler_id = ?,
        _status = 1,
        timestamp = ?
    WHERE data_type = ?
      AND _status = 0 AND MOD(id, ?)= ?
    ORDER BY `id` ASC
    LIMIT ?';
  PREPARE v_query FROM @v_query;
  EXECUTE v_query USING @v_handler_id, @v_timestamp, @v_data_type, @v_service_count, @v_request_type, @v_count;

  SELECT * FROM tbl_queue
    WHERE data_type = adata_type AND MOD(id, aservice_count) = arequest_type AND _status = 1;
END $$

DELIMITER ;