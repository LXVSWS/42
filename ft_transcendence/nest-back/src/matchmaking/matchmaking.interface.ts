import { Socket } from "socket.io";

export interface matchFriends {
    idP1: number;
    idP2: number;
    socketP1: Socket;
}
