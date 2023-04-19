<script lang="ts">
	export let socket;

	let showTimer = false;
	let timeLeft = 6;

	socket.on("startTimer", () => {
		showTimer = true;
	});

	socket.on("decrTimer", (counter: any) => {
		timeLeft = counter;
	});
</script>

{#if timeLeft > 0 && showTimer}
	<div>
		{timeLeft > 1 ? timeLeft - 1 : "GO!"}
	</div>
{/if}

<style>
	div {
		position: absolute;
		top: 50%;
		left: 50%;
		transform: translate(-50%, -50%);
		z-index: 2;
		font-size: 4rem;
		opacity: 70%;
		color: rgb(79, 79, 79);
	}
</style>
