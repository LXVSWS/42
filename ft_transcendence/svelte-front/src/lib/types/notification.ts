import type { FriendRequest } from "./friend-request"
import type { GameRequest } from "./game-request"

export type Notification = {
	type: string,
	data: FriendRequest | GameRequest
}