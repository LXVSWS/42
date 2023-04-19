<script lang="ts">
    import { goto } from "$app/navigation";
    import { blockUser, fetchBlockList, fetchBlockedUsersProfile, fetchId, fetchProfile, sendFriendRequest, unblockUser } from "$lib/api";
    import { chatSocket } from "$lib/stores/chat-socket";
    import { user } from "$lib/stores/user";
    import type { Profile } from "$lib/types/profile";
    import { onDestroy, onMount } from "svelte";
    import Loading from "./Loading.svelte";
    import { friends } from "$lib/stores/friends";
    import { sendGameRequest } from "$lib/utils/sendGameRequest";
    import { chatMessages } from "$lib/stores/chat-messages";

	export let setShow: any;
	export let username: string;
	export let admins: string[];
	export let owner: string;
	export let channelId: string;
	export let updateBlocked: (blocked: Profile[]) => void;

	let userProfile: Profile;
	let userIsFriend: boolean;
	let isLoading: boolean = true;
	let blockedList: number[];
	let userId: number;
	
	function handleClickOutside(event: any) {
    	if (!event.target.closest('#chat-modal')) {
			setShow(false);
		}
  	}

	onMount(async () => {
		document.addEventListener("click", handleClickOutside);

		try {
			userProfile = await fetchProfile(username);
			userId = await fetchId(username);
			userIsFriend = $friends.findIndex(friend => friend.profile.username === userProfile.username) !== -1;
			blockedList = await fetchBlockList();
		}
		catch (err) {
			setShow(false);
		}
		isLoading = false;
	});

	onDestroy(() => {
		document.removeEventListener("click", handleClickOutside);
	});
</script>

<dialog open={true}>
	{#if isLoading}
		<div class="loading">
			<Loading/>
		</div>
	{:else}
		<article id="chat-modal">
			<header on:click={() => goto(`/profile/${userProfile.username}`)} on:keypress>
				<img src={userProfile.avatar.url} alt="avatar"/>
				<span class="safe-words">{userProfile.username}</span>
			</header>
			{#if userProfile.username !== $user.profile.username}
				<body>
					<button on:click={() => sendGameRequest(userProfile.username)}>Challenge</button>
					{#if !userIsFriend}
						<button on:click={() => sendFriendRequest(userProfile.username).catch(err => {})}>Friend request</button>
					{/if}
					{#if (admins.includes($user.profile.username) || owner === $user.profile.username) && !admins.includes(userProfile.username) && owner != userProfile.username}
						<button on:click={() => {$chatSocket.emit('newAdmin', channelId, userProfile.username)}}>Give admin rights</button>
					{/if}
					{#if blockedList.findIndex(blocked => blocked === userId) === -1}
						<button on:click={async () => {
							try {
								await blockUser(userProfile.username); 
								updateBlocked(await fetchBlockedUsersProfile());
								setShow(false);
							}
							catch(err) {}
							}}>Block</button>
					{:else}
						<button on:click={async () => {
							try {
								await unblockUser(userProfile.username); 
								updateBlocked(await fetchBlockedUsersProfile());
								setShow(false);
							}
							catch(err) {}
							}}>Unblock</button>
					{/if}
					{#if (admins.includes($user.profile.username) || owner === $user.profile.username) && !admins.includes(userProfile.username) && owner != userProfile.username}
						<button on:click={() => {$chatSocket.emit('banUser', channelId, userProfile.username); setShow(false)}}>Ban</button>
						<button on:click={() => {$chatSocket.emit('kickUser', channelId, userProfile.username); setShow(false)}}>Kick</button>
						<button on:click={() => ($chatSocket.emit('muteUser', channelId, userProfile.username))}>Mute</button>
					{/if}
				</body>
			{/if}
		</article>
	{/if}
</dialog>

<style>
	.loading {
		width: 100%;
		height: 100%;
		display: flex;
		justify-content: center;
		align-items: center;
	}

	article {
		padding: 0;
		width: 300px;
	}

	header {
		display: flex;
		align-items: center;
		gap: 1rem;
		margin: 0;
		padding: 1rem;
	}

	header:hover {
		filter: brightness(1.2);
		cursor: pointer;
	}

	header img {
		border-radius: 50%;
		width: 96px;
		height: 96px;
        object-fit: cover;
        aspect-ratio: 1/1;
	}

	body {
		display: flex;
		flex-direction: column;
		gap: 1rem;
		padding: 1rem;
	}

	body button {
		margin-bottom: 0;
	}
</style>