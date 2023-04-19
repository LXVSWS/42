<script lang="ts">
    import { goto } from "$app/navigation";
    import { chatSocket } from "$lib/stores/chat-socket";
	import CryptoJS from 'crypto-js';

	export let closeModal: () => void;
	export let roomId: string | undefined;
	let password: string;
	let showError: boolean = false;

	function sendPassword() {
		const hashedPassword = !password || password === "" ? "" : CryptoJS.SHA256(password).toString();
		$chatSocket.emit('joinRoom', roomId, hashedPassword, (accepted: boolean) => {
			if (accepted) {
				closeModal();
				goto('/channels/' + roomId);
			}
			else {
				showError = true;
			}
		});
	}
</script>

<dialog open>
	<article>
	  <h3>Enter password :</h3>
		<input type="text" bind:value={password}>
		{#if showError}
		<span>Error ! Wrong password.</span>
		{/if}
	  <footer>
		<a href="/channels" role="button" class="secondary" on:click={closeModal}>Cancel</a>
		<a href=" " role="button" on:click={sendPassword}>Confirm</a>
	  </footer>
	</article>
  </dialog>