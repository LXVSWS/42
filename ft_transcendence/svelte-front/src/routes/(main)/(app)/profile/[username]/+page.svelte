<script lang="ts">
	import type { Match } from "$lib/types/match";
    import { fetchMatchHistory, fetchProfile } from "$lib/api";
    import { page } from "$app/stores";
    import type { Profile } from "$lib/types/profile";
    import { goto } from "$app/navigation";

	let nbMatchesToLoad = 5;
	let index = 0;
	let matches: Match[] = [];
	$: username = $page.url.pathname.split("/")[2];
	let userProfile: Profile;

	async function loadMore() {
		try {
			const data = await fetchMatchHistory(userProfile.username, index, nbMatchesToLoad);
			matches = [...matches, ...data];
			index += nbMatchesToLoad;
		} catch (err) {}
	}

	async function handleUsernameModified(username: string) {
		try {
			matches = [];
			index = 0;
			userProfile = await fetchProfile(username);
			await loadMore();
		} catch (err) {
			goto('/');
		}
	}

	$: handleUsernameModified(username);
</script>

<section>
	<div class="user">
		<img src={userProfile?.avatar?.url} alt="profile" />
		<div class="user-stats">
			<span>{userProfile?.username}</span>
			<div>
				<span style="color: var(--ins-color);;">{userProfile?.wins}</span>
				/
				<span style="color: var(--color);">0</span>
				/
				<span style="color: var(--del-color);;">{userProfile?.losses}</span>
			</div>
		</div>
	</div>
</section>

<section>
	<div class="table-match-history bg-light-dark">
		<h3>Match history</h3>
		<figure style="overflow: hidden;">
			<table>
				<thead>
					<tr>
						<th>Opponent</th>
						<th>Result</th>
						<th>Date</th>
					</tr>
				</thead>
				<tbody>
					{#each matches as match}
						<tr>
							<td class="opponent-cell">
								<span>{match.opponentProfile.username}</span>
							</td>
							<td class="result-cell">
								<div
									style="display: flex; flex-direction: column; min-width: 1.5em"
								>
									<span>{match.userScore}</span>
									<span>{match.opponentScore}</span>
								</div>
								{#if match.result == "won"}
									<iconify-icon
										icon="material-symbols:check-small-rounded"
										style="color: var(--ins-color); font-size: 2rem;"
									/>
								{:else if match.result == "lost"}
									<iconify-icon
										icon="ic:round-close"
										style="color: var(--del-color); font-size: 1.5rem; margin-left: 0.3rem;"
									/>
								{:else}
									<iconify-icon
										icon="ic:round-minus"
										style="color: var(--color); font-size: 1.5rem; margin-left: 0.3rem;"
									/>
								{/if}
							</td>
							<td>
								<span style="white-space: nowrap;"
									>{new Date(match.createdAt).toDateString()}
									{new Date(
										new Date(match.createdAt).getTime() +
											7200000
									).toLocaleTimeString("fr-MC")}
								</span>
							</td>
						</tr>
					{/each}
				</tbody>
			</table>
		</figure>
		{#if index === matches.length}
			<div style="display: flex; justify-content: center;">
				<button on:click={loadMore} class="secondary load-more-button">
					<iconify-icon
						icon="ic:round-plus"
						style="font-size: 1rem;"
					/>
				</button>
			</div>
		{/if}
	</div>
</section>

<style>
	.user {
		display: flex;
		flex-direction: column;
		align-items: center;
		gap: 1rem;
	}

	.user img {
		width: 50%;
		height: auto;
		border-radius: 50%;
		object-fit: cover;
		aspect-ratio: 1/1;
	}

	.user-stats {
		display: flex;
		flex-direction: column;
		align-items: center;
	}

	h3 {
		margin-bottom: 1rem;
		font-weight: normal;
		margin-left: 0.5rem;
	}

	.table-match-history {
		padding: 0.5rem 1rem 0rem 0.5rem;
		border-radius: 0 0 5px 5px;
	}

	figure {
		margin-bottom: -0.5rem;
	}

	thead {
		border: none;
	}

	.result-cell {
		display: flex;
		align-items: center;
	}

	.load-more-button {
		margin-top: -0.5rem;
		width: auto;
		border-radius: 50%;
		display: flex;
		justify-content: center;
		align-items: center;
		padding: 0.05rem;
	}
</style>
