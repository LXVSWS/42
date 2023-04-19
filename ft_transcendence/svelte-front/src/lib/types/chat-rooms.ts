export type chatRoom = {
	admins: number[];
	member: number[];
	banList: number[];
	ownerName: string;
	owner: number;
	capacity: number;
	id: string;
	name: string;
	isProtected: boolean;
	isPublic: boolean;
}