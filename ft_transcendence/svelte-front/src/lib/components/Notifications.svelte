<script lang="ts">
    import { acceptFriendRequest, acceptGameRequest, declineFriendRequest, declineGameRequest } from "$lib/api";
	import { notifications } from "$lib/stores/notifications";

	export let show: boolean;
	export let top: number;
</script>

{#if show && $notifications.length}
	<div class="notifications-container" style="--top:{top}px">
		<ul>
		{#each $notifications as notification}
			<li>
				<div>
					<img src={notification.data.creator.avatar.url} alt="avatar"/>
					<span>
						{notification.data.creator.username}
						{#if notification.type === "game-request"}
							challenged you
						{:else}
							wants to be your friend
						{/if}
					</span>
				</div>
				<div class="button-wrapper">
					{#if notification.type === "friend-request"}
						<button class="accept-button" on:click={() => acceptFriendRequest(notification.data.id)}>
							<iconify-icon icon="fluent-mdl2:accept-medium"></iconify-icon>
						</button>
						<button class="decline-button" on:click={() => declineFriendRequest(notification.data.id)}>
							<iconify-icon icon="radix-icons:cross-2"></iconify-icon>
						</button>
					{:else if notification.type === "game-request"}
						<button class="accept-button" on:click={() => acceptGameRequest(notification.data.creator.username)}>
							<iconify-icon icon="fluent-mdl2:accept-medium"></iconify-icon>
						</button>
						<button class="decline-button" on:click={() => declineGameRequest(notification.data.creator.username)}>
							<iconify-icon icon="radix-icons:cross-2"></iconify-icon>
						</button>
					{/if}
				</div>
			</li>
		{/each}
		</ul>
	</div>
{/if}

<style>
	.notifications-container {
		position: absolute;
		top: var(--top);
		right: 5px;
		background-color: #161b22;
		box-shadow: -5px 5px 5px #0d1117;
		width: 450px;
		max-width: 95vw;
		z-index: 10;
	}

	ul {
		margin: 0;
		padding: 0.5rem;
	}

	ul > :last-child {
		margin-bottom: 0;
	}

	ul li {
		background-color: #0d1117;
		padding: 0.3rem;
		list-style: none;
		margin-bottom: 0.5rem;
		display: flex;
		justify-content: space-between;
		align-items: center;
		gap: 1rem;
		border-radius: 5px;
	}

	ul li > :first-child {
		display: flex;
		align-items: center;
		gap: 0.5rem;
	}

	ul li > :first-child img {
		width: 48px;
		height: 48px;
		object-fit: cover;
		aspect-ratio: 1/1;
		border-radius: 50%;
	}

	button {
		border: none;
		--primary-focus: transparent;
		margin-bottom: 0;
		padding: 0.4rem;
		display: flex;
		justify-content: center;
		align-items: center;
	}

	button:hover iconify-icon {
		transform: scale(1.05);
	}

	.button-wrapper {
		display: flex;
		gap: 0.5rem;
		margin-left: 1rem;
	}

	.decline-button {
		background-color: var(--del-color);
	}

	.accept-button {
		background-color: var(--ins-color);
	}
</style>