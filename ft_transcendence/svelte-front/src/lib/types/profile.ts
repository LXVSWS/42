import type { Avatar } from "./avatar";

export type Profile = {
	avatar: Avatar,
	username: string,
	wins: number,
	losses: number
}