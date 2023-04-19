<script lang="ts">
    import { goto } from "$app/navigation";
    import { chatSocket } from "$lib/stores/chat-socket";
	import CryptoJS from 'crypto-js';

	let isPrivate: boolean = false;
	let name: string;
	let password: string;
	let capacity = 25;
	let error: string = "";
	let isDisabled: boolean = false;

	function createRoom() {
		if (!name || name.length > 10) {
			error = "Name cannot be longer than 10 characters or empty.";
		}
		else {
			const hashedPassword = !password || password === "" ? "" : CryptoJS.SHA256(password).toString();
			isDisabled = true;
			$chatSocket.emit('createRoom', name, capacity, hashedPassword, isPrivate, (id: string) => {
				goto(id);
			});
		}
	}
</script>

<section>
	<form>
		<label for="name">Name</label>
		<input
			type="text"
			name="name"
			placeholder="Name"
			bind:value={name}
			required
		/>
		<p style="color:red">{error}</p>

		<label for="size"
			>Capacity <kbd style="margin-left: 0.5rem;">{capacity}</kbd></label
		>
		<input
			type="range"
			min="1"
			max="50"
			bind:value={capacity}
			name="capacity"
		/>
		<label for="password">Password</label>
		<input
			type="text"
			name="password"
			placeholder="Password"
			bind:value={password}
		/>
		<small>Leave it empty if you don't want a password</small>

		<fieldset>
			<label for="switch">
				<input type="checkbox" id="switch" name="switch" role="switch" bind:checked={isPrivate}>
				Private
				<small style="padding-top: 0.5rem;margin:0;">Private rooms will not appear in the listing</small>
			</label>
		</fieldset>

		<button
			on:click={createRoom} disabled={isDisabled}>Create channel</button
		>
	</form>
</section>

<style>
	button {
		margin-top: 1.5rem;
	}
</style>
