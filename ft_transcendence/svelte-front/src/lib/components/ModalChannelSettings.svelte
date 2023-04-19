<script lang="ts">
    import { chatSocket } from "$lib/stores/chat-socket";
    import { user } from "$lib/stores/user";
	import CryptoJS from 'crypto-js';

	export let closeModal: () => void;
	export let channelId: string | undefined;
	let password: string = "";
	let isPrivate: boolean;

	$chatSocket.emit('getRoomScope', channelId, (isPublic: boolean) => {
		isPrivate = !isPublic;
	})

	function sendChange() {
		const hashedPassword = !password || password === "" ? "" : CryptoJS.SHA256(password).toString();
		$chatSocket.emit('roomUpdate', channelId, isPrivate, hashedPassword);
		closeModal();
	}

	function leaveRoom() {
		$chatSocket.emit('leaveRoom', channelId, $user.id);
		closeModal();
	}
</script>

<dialog open>
	<article>
	  <h3>Channel settings</h3>
	  <span>Change password : </span>
	  <input type="text" bind:value={password}>
	  <small>Change the password of the room, leave empty for none</small>

	  <fieldset>
		  <label for="switch">
			  <input type="checkbox" id="switch" name="switch" role="switch" bind:checked={isPrivate}>
			  Private
			  <small style="padding-top: 0.5rem;margin:0;">Private rooms will not appear in the listing</small>
			</label>
	  </fieldset>
		
	  <footer>
		<a href="/channels" role="button" id="leave" on:click={leaveRoom}>Leave Room</a>
		<a href=" " role="button" class="secondary" id="move" on:click={closeModal}>Cancel</a>
		<a href=" " role="button" id="move" on:click={sendChange}>Confirm</a>
	  </footer>
	</article>
  </dialog>

<style>
	footer {
		display: flex;
	}

	#leave {
		margin-right: auto;
	}

	#move {
		margin: 0 0 0 0.4rem;
	}
</style>