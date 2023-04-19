<script lang="ts">
	import { eventsSocket } from "$lib/stores/events-socket";
    import { onMount } from "svelte";

	let users: string[] = [];

	onMount(() => {
		$eventsSocket.emit("get-users", (data: string[]) => {
			users = data;
		});
		
		$eventsSocket.on("user-connected", (data: string) => {
			users = [...users, data];
		});

		$eventsSocket.on("user-disconnected", (data: string) => {
			const index = users.findIndex(x => x === data);
			if (index !== -1) {
				users.splice(index, 1);
				users = users;
			}
		});
	});	
</script>

<section>
	<h3>Users logged in</h3>
	<ul>
		{#each users as user}
			<li>
				<a href={`/profile/${user}`}>{user}</a>
			</li>
		{/each}
	</ul>
</section>

<style>
	li {
		cursor: pointer;
	}
</style>