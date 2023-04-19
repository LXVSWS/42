<script lang="ts">
	export let socket;
	let showTimer = false;

	let timeLeft = 5;
	socket.on("decoTimer", () => {
		timeLeft = 5;
		showTimer = true;
		let id = setInterval(() => {
			timeLeft -= 1;
			if (timeLeft == 0) clearInterval(id);
		}, 1000);
	});
</script>

{#if timeLeft > 0 && showTimer}
	<div>
		A player disconnected, game end in : {timeLeft}
	</div>
{/if}

<style>
	div {
		position: absolute;
		top: 30%;
		left: 50%;
		transform: translate(-50%, -50%);
		z-index: 2;
		text-align: center;
		font-size: 1.5rem;
		opacity: 70%;
		color: rgb(79, 79, 79);
	}
</style>
