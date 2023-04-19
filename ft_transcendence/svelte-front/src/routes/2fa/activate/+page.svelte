<script lang="ts">
	import { goto } from "$app/navigation";
	import CanvasQrCode from "$lib/components/CanvasQrCode.svelte";
	import { onMount } from "svelte";
	import { user } from "$lib/stores/user";
    import { generateTwoFactorAuthenticationQrCode, loginUserWithTwoFactorAuthentication, turnOnTwoFactorAuthentication } from "$lib/api";

	let qrCodeData = "";
	let code = "";
	let error = "";

	async function verifyCode() {
		try {
			await turnOnTwoFactorAuthentication(code);
			await loginUserWithTwoFactorAuthentication(code);
			error = "";
			goto("/");
		} catch (err) {
			error = err.message;
		}
	}

	onMount(async () => {
		qrCodeData = await generateTwoFactorAuthenticationQrCode();
	});
</script>

<h3>Scan with Google Authenticator</h3>
<CanvasQrCode {qrCodeData} width={300} height={300} />
<input name="code" bind:value={code} />
{#if error}
	<span class="error">{error}</span>
{/if}
<button type="submit" on:click={verifyCode}>Verify code</button>

<style>
	h3 {
		margin-bottom: 1.5rem;
	}

	input {
		margin-top: 2rem;
	}

	.error {
		margin-top: -0.5rem;
		margin-bottom: 1.5rem;
		color: var(--del-color);
		font-size: 0.8rem;
	}
</style>
