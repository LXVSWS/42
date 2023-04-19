<script lang="ts">
	import NavbarMobile from "$lib/components/NavbarMobile.svelte";
    import Navbar from "$lib/components/Navbar.svelte";
</script>

<header>
	<div class="navbar-mobile">
		<NavbarMobile/>
	</div>
	<div class="navbar">
		<Navbar/>
	</div>
</header>
<main class="container">
	<slot/>
</main>
<footer>
	<div>
		<span>Made with love by <a href="https://github.com/nferre">him</a>, <a href="https://github.com/LXVSWS">him</a>, <a href="https://github.com/yo-dst">him</a> and <a href="https://onlyfans.com/corinnakopf">her </a></span>
	</div>
</footer>

<style>
	header {
		margin-bottom: 25px;
	}

	main {
		margin-bottom: 75px;
		max-width: 500px;
	}

	.navbar-mobile {
		display: none;
	}

	.navbar {
		display: block;
	}

	footer {
		position: absolute;
		height: 50px;
		left: 0;
		bottom: 0;
		width: 100%;
		background-color: #161b22;
		display: flex;
		justify-content: center;
		align-items: center;
		color: var(--color);
	}

	@media (max-width: 700px) {
		.navbar-mobile {
			display: block;
		}

		.navbar {
			display: none;
		}
	}
</style>
