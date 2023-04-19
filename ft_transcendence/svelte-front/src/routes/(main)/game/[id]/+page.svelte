<script lang="ts">
	import { goto } from "$app/navigation";
	import { page } from "$app/stores";
	import { io } from "socket.io-client";
	import Pong from "./pong.svelte";
	import TurnPhone from "$lib/components/turnPhone.svelte";
	import { waitFlip } from "./pong";
	import { user } from "$lib/stores/user";
    import { eventsSocket } from "$lib/stores/events-socket";
	import { apiUrl } from "$lib/environment";

	let turnPhone = true;
	let id = $page.params.id;
	let roomExist: boolean = false;
	let gameMode = 0;
	let socket = io(`${apiUrl}/game`);
	let isMobile = false;
	if (
		/Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(
			navigator.userAgent
		)
	) {
		isMobile = true;
	}

	// verify that room Exist
	socket.emit("checkId", id, $user?.id);

	socket.on("found", (gamemode) => {
		roomExist = true;
		gameMode = gamemode;
		$eventsSocket.emit("join-game");
	});

	waitFlip().then((newTurnPhone) => {
		turnPhone = newTurnPhone;
	});
</script>

{#if roomExist && (!turnPhone || !isMobile)}
	<Pong {gameMode} {socket} />
{:else if turnPhone && isMobile && roomExist}
	<TurnPhone />
{:else}
	<div class="container">
		<h2 style="text-align:center">RoomId not found</h2>
		<a href="/" role="button" style="">Go back home</a>
  	</div>
{/if}

<style>
	.container {
	  display: flex;
	  flex-direction: column;
	  justify-content: center;
	  align-items: center;
	  height: 100vh; /* set the height of the container to the height of the viewport */
	}
</style>
  