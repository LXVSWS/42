<script lang="ts">
	import { user } from "$lib/stores/user";
	import { goto } from "$app/navigation";
	import { onMount } from "svelte";
    import { fetchBlockedUsersProfile, logoutUser, turnOffTwoFactorAuthentication, unblockUser, updateUserAvatar, updateUserUsername } from "$lib/api";
    import Loading from "$lib/components/Loading.svelte";
    import type { Profile } from "$lib/types/profile";

	let newUsername = "";
	let files: any;
	let isTwoFactorAuthenticationEnabled: boolean;
	let updateUsernameError = "";
	let updateAvatarError = "";
	let blockedUsers: Profile[];
	let isLoading = true;
	
	async function updateUsername() {
		try {
			await updateUserUsername(newUsername);
			updateUsernameError = "";
		} catch (err) {
			updateUsernameError = err.message;
		}
	}

	async function updateAvatar() {
		try {
			const reader = new FileReader();
			reader.addEventListener("load", async () => {
				const newAvatar = reader.result;
				if (typeof newAvatar !== "string") {
					throw "Error: can't load image";
				}
				await updateUserAvatar(newAvatar);
				updateAvatarError = "";
			});

			if (files && files[0]) {
				const type = files[0].type;
				if (type !== "image/jpg"
					&& type !== "image/jpeg"
					&& type !== "image/png") {
					updateAvatarError = "Only jpg, jpeg or png files are allowed";
					return;
				}
				reader.readAsDataURL(files[0]);
			}
		} catch (err) {
			updateAvatarError = err.msg;
		}
	}

	async function toggleTwoFactorAuthentication() {
		if (isTwoFactorAuthenticationEnabled) {
			goto("/2fa/activate");
		} else {
			try {
				await turnOffTwoFactorAuthentication();
			} catch (err) {
				isTwoFactorAuthenticationEnabled = true;
			}
		}
	}

	async function logout() {
		try {
			await logoutUser();
		} catch (err) {}
	}

	onMount(async () => {
		try {
			blockedUsers = await fetchBlockedUsersProfile();
			isLoading = false;
		}
		catch (err) {}
		newUsername = $user.profile.username;
		isTwoFactorAuthenticationEnabled = $user.isTwoFactorAuthenticationEnabled;
	});
</script>

<section>
	<h3>Modify your account</h3>

	<label for="username">Username</label>
	<div class="input-button-container">
		<input name="username" bind:value={newUsername} />
		<button on:click={updateUsername}>Update</button>
		{#if updateUsernameError}
			<span class="error">{updateUsernameError}</span>
		{/if}
	</div>

	<label for="avatar">Avatar </label>
	<div class="input-button-container">
		<input
			name="avatar"
			type="file"
			bind:files
			accept="image/png image/jpeg image/jpg"
		/>
		<button on:click={updateAvatar}>Update</button>
		{#if updateAvatarError}
			<span class="error">{updateAvatarError}</span>
		{/if}
	</div>

	<label for="isTwoFactorAuthenticationEnabled">
		<input
			type="checkbox"
			name="isTwoFactorAuthenticationEnabled"
			role="switch"
			bind:checked={isTwoFactorAuthenticationEnabled}
			on:change={toggleTwoFactorAuthentication}
		/>
	{#if isTwoFactorAuthenticationEnabled}
		<span>Disable two factor authentication</span>
	{:else}
		<span>Enable two factor authentication</span>
	{/if}
	</label>
</section>

{#if isLoading}
<Loading/>
{:else}
<section class="bg-light-dark" style="padding: 1rem; border-radius: 5px; margin-top: 4rem;">
	<h3>Users blocked</h3>
	<ul>
		{#each blockedUsers as userBlocked}
			<li>
				<div>
					<img src={userBlocked.avatar.url} alt="avatar"/>
					<span class="safe-words">{userBlocked.username}</span>
				</div>
				<button on:click={() => {unblockUser(userBlocked.username); blockedUsers.splice(blockedUsers.indexOf(userBlocked), 1); blockedUsers = blockedUsers}}>Unblock</button>
			</li>
		{/each}
	</ul>
</section>
{/if}
<div class="logout-wrapper">
	<h3>Log in with another account</h3>
	<a href="/" role="button" on:click={logout} class="contrast outline">
		<iconify-icon icon="material-symbols:logout" />
		Log out
	</a>
</div>

<style>
	h3 {
		margin-bottom: 1rem;
		font-weight: normal;
	}

	.logout-wrapper {
		margin-top: 50px;
		display: block;
	}

	.logout-wrapper a {
		width: 100%;
		display: flex;
		justify-content: center;
		align-items: center;
		gap: 0.5rem;
	}

	.logout-wrapper a:hover {
		background-color: var(--contrast);
		color: black;
	}

	ul {
		padding: 0;
		margin: 0;
	}

	ul li {
		list-style: none;
		display: flex;
		justify-content: space-between;
		align-items: center;
		margin-bottom: 0.5rem;
		background-color: #11191f;
		border-radius: 5px;
		padding: 0.5rem;
		gap: 1rem;
	}

	ul li > :first-child {
		display: flex;
		align-items: center;
		gap: 1rem;
	}

	ul li img {
		width: 64px;
		height: 64px;
		object-fit: cover;
		aspect-ratio: 1/1;
		border-radius: 50%;
	}

	ul li button {
		width: auto;
		height: auto;
		margin-bottom: 0;
	}

	@media (max-width: 700px) {
		.logout-wrapper {
			display: none;
		}
	}
</style>
