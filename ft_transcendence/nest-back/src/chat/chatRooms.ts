import { v4 } from 'uuid';

export class ChatRoom {
	public name: string;
	public admins: number[] = [];
	public member: number[] = [];
	public banList: number[] = [];
	public muteList: number[] = [];
	public owner: number;
	public password: string;
	public capacity: number;
	public id: string;
	public isPublic: boolean;
	public isProtected: boolean;
	public ownerName: string;

	constructor(owner: number, name: string, capacity: number, password: string, isPrivate: boolean) {
		this.name = name;
		this.owner = owner;
		this.isPublic = isPrivate === true ? false : true;
		if (password) {
			this.password = password;
			this.isProtected = true;
		}
		else
			this.isProtected = false;
		this.capacity = capacity;
		this.id = v4();
	}

	addUser(userId: number) {
		if (this.capacity > (this.member.length + this.admins.length + 1) && !this.member.includes(userId) && !this.admins.includes(userId) && this.owner != userId) {
			this.member.push(userId);
		}
	}

	update(isPrivate: boolean, password: string) {
		this.isPublic = isPrivate === true ? false : true;
		if (password && password != "") {
			this.password = password;
			this.isProtected = true;
		}
		else this.isProtected = false;
	}

	mute(userId: number) {
		if (!this.muteList.includes(userId)) {
			this.muteList.push(userId);
		}
	}

	unmute(userId: number) {
		const index = this.muteList.findIndex(user => user === userId);
		if (index != -1)
			this.muteList.splice(index, 1);
	}

	deleteUser(userId: number){
		if (this.member.includes(userId)) this.member.splice(this.member.findIndex((member) => (member === userId)), 1);
		else if (this.admins.includes(userId)) this.admins.splice(this.admins.findIndex((admins) => (admins === userId)), 1);
		else if (userId === this.owner) {
			if (this.admins.length > 0) {
				this.owner = this.admins[0];
				this.admins.splice(0);
			}
			else if (this.member.length > 0) {
				this.owner = this.member[0];
				this.member.splice(0);
			}
			else this.owner = undefined;
		}
	}

	addAdmin(userId: number) {
		if (!this.admins.includes(userId)) {
			if (this.member.includes(userId)) {
				this.deleteUser(userId);
			}
			this.admins.push(userId);
		}
	}

	ban(userId: number) {
		if (!this.banList.includes(userId))
			this.banList.push(userId);
	}

	unban(userId: number) {
		const index = this.banList.findIndex(user => user === userId);
		if (index != -1)
			this.banList.splice(index, 1);
	}

}