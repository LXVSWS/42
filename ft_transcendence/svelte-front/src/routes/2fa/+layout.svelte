<main>
	<div>
		<slot></slot>
	</div>
</main>

<style>
	main {
		display: flex;
		align-items: center;
		justify-content: center;
		padding: 1rem;
	}

	main > div {
		max-width: 500px;
		display: flex;
		flex-direction: column;
		justify-content: center;
	}
</style>