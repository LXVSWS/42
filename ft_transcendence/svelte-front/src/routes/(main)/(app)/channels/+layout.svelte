<script lang="ts">
    import Loading from "$lib/components/Loading.svelte";
	import { chatSocket } from "$lib/stores/chat-socket";

</script>
{#if $chatSocket != undefined}
<slot />
{:else}
<Loading/>
{/if}