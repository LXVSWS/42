<script lang="ts">
    import { goto } from "$app/navigation";
	import { apiUrl, intraLoginUrl } from "$lib/environment";

	// let username: string;

	// async function createFakeUser() {
	// 	await fetch(`${apiUrl}/users/fake`, {
	// 		method: "POST",
	// 		headers: {
	// 			"Content-Type": "application/json",
	// 		}
	// 	});
	// }
</script>

<div class="page">
	<div class="container">
		<a role="button"
			class="contrast outline"
			href={intraLoginUrl}
		>
			<iconify-icon icon="material-symbols:login" />
			Log In
		</a>
		
		<!-- <input bind:value={username} style="margin-top: 2rem;"/>
		<button on:click={() => goto(`${apiUrl}/auth/username?username=${username}`)}>Login with username</button>
	
		<button on:click={createFakeUser}>Create fake user</button> -->
	</div>
</div>

<style>
	.page {
		width: 100vw;
		height: 100vh;
		display: flex;
		justify-content: center;
		align-items: center;
	}

	.container {
		max-width: 500px;
		display: flex;
		flex-direction: column;
	}

	a {
		display: flex;
		justify-content: center;
		align-items: center;
	}
</style>