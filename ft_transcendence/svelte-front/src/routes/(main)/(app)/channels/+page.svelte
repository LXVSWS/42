<script lang="ts">
    import { goto } from "$app/navigation";
    import { user } from "$lib/stores/user";
    import type { chatRoom } from "$lib/types/chat-rooms";
    import { onMount } from "svelte";
	import { chatSocket } from "$lib/stores/chat-socket";
    import ModalPasswordChannels from "$lib/components/ModalPasswordChannels.svelte";
	
	let rooms: chatRoom[] = [];
	let joinedRooms: chatRoom[] = [];
	let isModalShowing = false;

	function getJoinedRooms(rooms: chatRoom[]): chatRoom[] {
		return rooms.filter(room => {
			if (($user.id === room.owner)
				|| (room.admins.indexOf($user.id) !== -1)
				|| (room.member.indexOf($user.id)) !== -1) {
				return true;
			}
			return false;
		});
	}

	function roomIsJoined(room: chatRoom) {
		for (let i = 0; i < joinedRooms.length; i++) {
			if (joinedRooms[i].id === room.id) {
				return true;
			}
		}
		return false;
	}

	function joinRoom(id: string) {
		$chatSocket.emit('joinRoom', id, undefined, (found: boolean) => {
			if (found) goto('/channels/' + id);
		});
	}

	function closeModal() {
		isModalShowing = false;
	}

	$: joinedRooms = getJoinedRooms(rooms);

	onMount(() => {
		$chatSocket.emit('getRooms', (data: chatRoom[]) => {
			rooms = data;
		});
		
		$chatSocket.on('roomUpdate', (data: chatRoom[]) => {
			rooms = data;
		});
	});
</script>

<section>
	<a href="/channels/create" role="button" style="width: 100%;">Create your channel</a>
</section>

<section>
	<h3>Joined channels</h3>
	<ul>
		{#each joinedRooms as room}
			<li>
				<div class="channel-left">
					<div class="users">
						<span>{room.member.length + room.admins.length + 1} / {room.capacity}</span>
						<iconify-icon icon="fa-solid:user-friends"></iconify-icon>	
					</div>
					<div class="channel-name">
						{room.name}
						<small><i>{room.ownerName}</i></small>
					</div>
				</div>
				<div class="channel-right">
						<button class="secondary" on:click={() => {joinRoom(room.id)}}>
							<iconify-icon icon="material-symbols:open-in-browser"></iconify-icon>
						</button>
				</div>
			</li>
		{/each}
	</ul>
</section>

<section>
	<h3>Channels</h3>
	<ul>
		{#each rooms as room}
			{#if room.isPublic && !roomIsJoined(room)}
				<li>
					<div class="channel-left">
						<div class="users">
							<span>{room.member.length + room.admins.length + 1} / {room.capacity}</span>
							<iconify-icon icon="fa-solid:user-friends"></iconify-icon>	
						</div>
						<div class="channel-name">
							{room.name}
							<small><i>{room.ownerName}</i></small>
						</div>
					</div>
					<div class="channel-right">
						{#if room.member.length + room.admins.length + 1 >= room.capacity}
							<p>room filled</p>
						{:else if room.isProtected }
							<iconify-icon icon="material-symbols:lock" style="font-size: 1.5rem;"></iconify-icon>
							<button class="secondary" on:click={() => {isModalShowing = true}}>
								<iconify-icon icon="material-symbols:open-in-browser"></iconify-icon>
							</button>
						{:else}
							<button class="secondary" on:click={() => {joinRoom(room.id)}}>
								<iconify-icon icon="material-symbols:open-in-browser"></iconify-icon>
							</button>
						{/if}
					</div>
					{#if isModalShowing}
						<ModalPasswordChannels closeModal={closeModal} roomId={room.id}/>
					{/if}
				</li>
			{/if}
		{/each}
	</ul>
</section>

<style>
	h3 {
		margin-bottom: 0;
	}

	ul {
		padding: 0;
		background-color: #090D10;
		padding: 0.5rem 1rem 0.5rem 0.5rem;
		border-radius: 0 0 5px 5px;
	}

	ul > li {
		background-color: var(--background-color);
		list-style-type: none;
		padding: 0.5rem 1rem;
		display: flex;
		justify-content: space-between;
		align-items: center;
	}

	ul > li button {
		width: auto;
		height: auto;
		padding: 0.3rem;
		display: flex;
		justify-content: center;
		align-items: center;
		margin-bottom: 0;
	}

	iconify-icon {
		font-size: 1.3rem;
	}

	.channel-right {
		display: flex;
		align-items: center;
		gap: 1rem;
	}

	.channel-left {
		display: flex;
		align-items: center;
	}

	.users {
		display: flex;
		justify-content: space-between;
		align-items: center;
		width: 5.5rem;
	}

	.channel-name {
		margin-left: 1.5rem;
		display: flex;
		flex-direction: column;
	}
</style>