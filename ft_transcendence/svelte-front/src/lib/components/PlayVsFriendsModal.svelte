<script lang="ts">
    import { friends } from "$lib/stores/friends";
    import type { Friend } from "$lib/types/friend";
    import { sendGameRequest } from "$lib/utils/sendGameRequest";
	import { onDestroy, onMount } from "svelte";

	export let setShow: any;

	let friendsConnected: Friend[] = [];

	function getFriendsConnected(friends: Friend[]) {
		friendsConnected = friends.filter(friend => friend.isConnected === true);
	}

	function handleClickOutside(event: any) {
    	if (!event.target.closest('#play-vs-friend-modal')) {
			setShow(false);
		}
  	}

	$: getFriendsConnected($friends);

	onMount(async () => {
		document.addEventListener("click", handleClickOutside);
	});

	onDestroy(() => {
		document.removeEventListener("click", handleClickOutside);
	});
</script>

<dialog open={true}>
	<article id="play-vs-friend-modal">
		<header>
			<h3>Send game invitation</h3>
			<button on:click={() => setShow(false)} class="close-button contrast outline">
				<iconify-icon icon="charm:cross" style="font-size: 1.7rem;"/>
			</button>
		</header>
		<body>
			<ul>
				{#each friendsConnected as friend}
					<li>
						<div>
							<img src={friend.profile.avatar.url} alt="avatar"/>
							<span class="safe-words">{friend.profile.username}</span>
						</div>
						<div>
							{#if friend.isInGame}
								<iconify-icon icon="mdi:sword-fight" style="font-size: 2rem;"></iconify-icon>
							{/if}
							<button on:click={() => sendGameRequest(friend.profile.username)}>
								<iconify-icon icon="material-symbols:auto-read-play-outline-sharp" style="font-size: 1.5rem;"></iconify-icon>
							</button>
						</div>
					</li>
				{/each}
			</ul>
		</body>
	</article>
</dialog>

<style>
	article {
		width: 450px;
		max-width: 90vw;
		padding: 0;
	}

	header {
		margin: 0;
		display: flex;
		justify-content: space-between;
		align-items: center;
		gap: 1rem;
	}

	header h3 {
		margin-bottom: 0;
	}

	.close-button {
		padding: 0.2rem;
		margin-bottom: 0;
		display: flex;
		justify-content: center;
		align-items: center;
		width: auto;
		height: auto;
	}

	.close-button:hover iconify-icon {
		transform: scale(1.05);
	}

	ul {
		padding: 0.5rem 0.5rem 0 0.5rem;
		margin: 0;
	}

	ul li {
		list-style: none;
		margin-bottom: 0.5rem;
		display: flex;
		align-items: center;
		justify-content: space-between;
		gap: 2rem;
		padding: 0.5rem;
		background-color: var(--card-sectionning-background-color);
		border-radius: 5px;
	}

	ul li > :first-child {
		display: flex;
		align-items: center;
		gap: 1rem;
	}

	ul li > :first-child img {
		height: 64px;
		width: 64px;
		object-fit: cover;
		aspect-ratio: 1/1;
		border-radius: 50%;
	}

	ul li > :last-child {
		display: flex;
		justify-content: flex-end;
		align-items: center;
		gap: 1rem;
	}

	ul li > :last-child button {
		margin-bottom: 0;
		width: auto;
		height: auto;
		display: flex;
		justify-content: center;
		align-items: center;
	}

	ul li > :last-child button:hover iconify-icon {
		transform: scale(1.05);
	}
</style>