export type chatMessage = {
	[id: string]: {
		message: string;
		username: string;
	}[];
}