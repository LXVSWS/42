import { Controller, Get } from '@nestjs/common';
import { ChatService } from './chat.service';

@Controller('chat')
export class ChatController {
	constructor(private readonly ChatService: ChatService) {}

	@Get()
	main(): any[] {
		return this.ChatService.getData();
	}
}
