db.counters.ensureIndex( {"name":1}, {unique:true} ); 

db.pgreq.dropIndex( {"pers_auid":1} );
db.pgreq.dropIndex( {"guild_auid":1} );
db.pgreq.dropIndex( {"created":1} );
db.pgreq.ensureIndex( {"pers_auid": 1}, {unique:false} );
db.pgreq.ensureIndex( {"guild_auid": 1}, {unique:false} );
db.pgreq.ensureIndex( {"created": 1}, {unique:false} );

db.sieges.dropIndex( {"target":1} );
db.sieges.ensureIndex( {"target":1}, {unique:true} );

db.quests.dropIndex( {"key":1} ); 
db.quests.ensureIndex( {"key":1}, {unique:true,sparse:true} ); 
db.quests.dropIndex( {"last_id":1} ); 
db.quests.ensureIndex( {"last_id":1}, {unique:true,sparse:true} );

db.quests.dropIndex( {"key":1} ); 
db.quests.ensureIndex( {"key":1}, {unique:true,sparse:true} ); 
db.quests.dropIndex( {"last_id":1} ); 
db.quests.ensureIndex( {"last_id":1}, {unique:true,sparse:true} );
db.quests.dropIndex( {"auidsKey":1} ); 
db.quests.ensureIndex( {"auidsKey":1}, {unique:true,sparse:true} ); 

db.punished.dropIndex( {"_id":1} ); 
db.punished.ensureIndex( {"_id":1}, {unique:true,sparse:true} ); 

db.events.dropIndex( {"_id":1} ); 
db.events.ensureIndex( {"_id":1}, {unique:true,sparse:true} ); 
