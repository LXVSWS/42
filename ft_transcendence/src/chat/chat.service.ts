import { Injectable } from '@nestjs/common';

@Injectable()
export class ChatService {
	tab: any[] = ["message", "message2"];

	getData(): any[] {
		return this.tab;
	}
}
