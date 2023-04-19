<script lang="ts">
    import type { Friend } from "$lib/types/friend";
    import { acceptFriendRequest, declineFriendRequest, removeFriend, sendFriendRequest } from "$lib/api";
	import { friendRequests } from "$lib/stores/friend-requests";
    import { friends } from "$lib/stores/friends";
	
	let friendsSorted: Friend[] = [];
	let sendRequestValue = "";
	let sendRequestError = "";

	function sortFriends(friends: Friend[]) {
		let tmp = friends;
		return tmp.sort((a, b) => {
			if (a.isConnected && b.isConnected)
				return 0;
			else if (a.isConnected) {
				return -1;
			}
			return 1;
		});
	}

	async function sendRequest() {
		try {
			await sendFriendRequest(sendRequestValue);
			sendRequestError = "";
		} catch (err) {
			sendRequestError = err.message;
		}
	}

	$: friendsSorted = sortFriends($friends);
</script>

<section>
	<h3>Add a friend</h3>
	<div class="input-button-container" style="margin-bottom: -0.5rem;">
		<input type="text" placeholder="Username" bind:value={sendRequestValue} />
		<button on:click={sendRequest} style="background-color: var(--ins-color); border:none;">
			<iconify-icon icon="fluent-mdl2:add-friend" style="font-size: 1.5rem"/>
		</button>
	</div>
	{#if sendRequestError}
		<span class="error">{sendRequestError}</span>
	{/if}
</section>

<section>
	<div class="list-container bg-light-dark">
		<h3>Friends</h3>
		<ul>
		{#each friendsSorted as friend}
			<li>
				<a href={`/profile/${friend.profile.username}`}>
					<div class="friend-profile">
						<img src={friend.profile.avatar.url} alt="friend"/>
						{#if friend.isInGame}
						<iconify-icon icon="mdi:sword-fight" style="font-size: 2rem;"></iconify-icon>
						{/if}
						<span>{friend.profile.username}</span>
						<div class:online={friend.isConnected}></div>
					</div>
				</a>
				<button on:click={() => removeFriend(friend.profile.username)} style="background-color: var(--del-color);">
					<iconify-icon icon="charm:cross" style="font-size: 1.5rem;"/>
				</button>
			</li>
		{/each}
		</ul>
	</div>
</section>

<section>
	<div class="list-container bg-light-dark">
		<h3>Friend requests received</h3>
		<ul>
		{#each $friendRequests as friendRequest}
			<li>
				<a href={`/profile/${friendRequest.creator.username}`}>
					<img src={friendRequest.creator.avatar.url} alt="friend-request-creator"/>
					<span>{friendRequest.creator.username}</span>
				</a>
				<div class="friend-request-buttons">
					<button on:click={() => acceptFriendRequest(friendRequest.id)} style="background-color: var(--ins-color);">
						<iconify-icon icon="fluent-mdl2:accept-medium" style="font-size: 1.5rem;"></iconify-icon>
					</button>
					<button on:click={() => declineFriendRequest(friendRequest.id)} style="background-color: var(--del-color);">
						<iconify-icon icon="charm:cross" style="font-size: 1.5rem;"/>
					</button>
				</div>
			</li>
		{/each}
		</ul>
	</div>
</section>

<style>
	h3 {
		margin-bottom: 1rem;
		font-weight: normal;
		margin-left: 0.5rem;
	}

	ul {
		padding: 0;
		margin: 0;
		width: 100%;
	}

	ul > li {
		display: flex;
		justify-content: space-between;
		align-items: center;
		background-color: #0d1117;
		list-style-type: none;
		border-radius: 5px;
		margin-bottom: 0.7rem;
		padding: 0.5rem 1rem;
	}

	ul > li:hover {
		background-color: #33383E;
		cursor: pointer;
	}

	ul > li:hover button {
		display: flex;
	}

	ul > li > a {
		width: 80%;
		display: flex;
		align-items: center;
		text-decoration: none;
		color: #f0f6fc;
		gap: 0.5rem;
	}

	ul > li > a:hover img {
		transform: scale(1.05);
	}

	ul > li img {
		height: 3.5rem;
		width: auto;
		object-fit: cover;
		aspect-ratio: 1/1;
		border-radius: 50%;
	}

	ul > li button {
		display: none;
		width: auto;
		height: auto;
		margin-bottom: 0;
		justify-content: center;
		align-items: center;
		border: none;
	}

	ul > li button:hover {
		opacity: 0.9;
	}

	.friend-request-buttons {
		display: flex;
		gap: 0.5rem;
		align-items: center;
	}

	.friend-profile {
		position: relative;
		display: flex;
		align-items: center;
		gap: 0.5rem;
	}

	.online {
		position: absolute;
		top: 0;
		left: 0;
		background-color: var(--ins-color);
		width: 16px;
		height: 16px;
		border-radius: 50%;
		box-shadow: 0 0 5px black;
		z-index: 9;
	}

	.error {
		color: var(--del-color);
	}

	@media (max-width: 700px) {
		ul > li button {
			display: flex;
		}
	}
</style>
