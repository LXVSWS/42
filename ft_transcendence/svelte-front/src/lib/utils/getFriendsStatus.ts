import type { Friend } from "$lib/types/friend";
import type { Profile } from "$lib/types/profile";
import { isUserConnected } from "./isUserConnected";
import { isUserInGame } from "./isUserInGame";

export async function getFriendsStatus(friendsProfile: Profile[]): Promise<Friend[]> {
	return await Promise.all(friendsProfile.map(async profile => {
		const isConnected = await isUserConnected(profile.username);
		const isInGame = await isUserInGame(profile.username);
		return {
			isConnected,
			isInGame,
			profile
		};
	}));
}
