struct Server {
    1: string name,
    2: string addr,
    3: i16 on,
    4: i16 rdy,
    5: double ka
}

service ServerInfo {
    list<Server> getServers()
}
