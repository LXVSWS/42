<script lang="ts">
	import { goto } from "$app/navigation";
    import { loginUserWithTwoFactorAuthentication } from "$lib/api";
	import { apiUrl } from "$lib/environment";

	let code = "";
	let error = "";

	async function verifyCode() {
		try {
			await loginUserWithTwoFactorAuthentication(code);
			error = "";
			goto(`${apiUrl}/2fa/redirect`);
		} catch (err) {
			error = err.message;
		}
	}
</script>

<h3>Google Authenticator code</h3>
<input name="code" bind:value={code} />
{#if error}
	<span class="error">{error}</span>
{/if}
<button on:click={verifyCode}>Verify</button>

<style>
	.error {
		margin-top: -0.5rem;
		margin-bottom: 1.5rem;
		color: var(--del-color);
		font-size: 0.8rem;
	}
</style>
