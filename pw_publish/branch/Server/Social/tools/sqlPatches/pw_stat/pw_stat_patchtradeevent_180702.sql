use pw_stat;

drop procedure if exists ApplyPatch180702;

delimiter $$

create procedure ApplyPatch180702()
patch:begin
  UPDATE tbl_tradeevent_exps SET event_id=1;

  -- search and delete duplicates 
  DELETE n1 FROM tbl_tradeevent_exps n1, tbl_tradeevent_exps n2 WHERE n1.experience < n2.experience AND n1.auid = n2.auid;
  
  select "INFO: SUCCESS! tbl_tradeevent_exps event_id column has switched to '1' value. All auid duplicates has deleted" as `log`;
  
end$$

delimiter ;

call ApplyPatch180702();

drop procedure ApplyPatch180702;

