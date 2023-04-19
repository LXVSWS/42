<script lang="ts">
  import { onMount } from "svelte";

	export let qrCodeData: string;
	export let width: number;
	export let height: number;

	let canvas: HTMLCanvasElement;
	let ctx: CanvasRenderingContext2D;

	function drawImg(imgDataUrl: string) {
		if (!ctx) {
			return;
		}
		const img = new Image();
		img.src = imgDataUrl;
		img.addEventListener("load", () => {
			ctx.drawImage(img, (width - img.width) / 2, (height - img.height) / 2);
		});
	}

	$: drawImg(qrCodeData);

	onMount(() => {
		ctx = canvas.getContext('2d');
		ctx.fillStyle = "black";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
	});
</script>

<canvas 
	bind:this={canvas}
	{width}
	{height}
></canvas>
