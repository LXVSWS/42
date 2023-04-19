import type { FriendRequest } from "$lib/types/friend-request";
import { writable } from "svelte/store";

export const friendRequests = writable<FriendRequest[]>([]);