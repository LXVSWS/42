export { matchers } from './matchers.js';

export const nodes = [() => import('./nodes/0'),
	() => import('./nodes/1'),
	() => import('./nodes/2'),
	() => import('./nodes/3'),
	() => import('./nodes/4'),
	() => import('./nodes/5'),
	() => import('./nodes/6'),
	() => import('./nodes/7'),
	() => import('./nodes/8'),
	() => import('./nodes/9'),
	() => import('./nodes/10'),
	() => import('./nodes/11'),
	() => import('./nodes/12'),
	() => import('./nodes/13'),
	() => import('./nodes/14'),
	() => import('./nodes/15'),
	() => import('./nodes/16'),
	() => import('./nodes/17')];

export const server_loads = [];

export const dictionary = {
	"/(main)/(app)": [6,[2,3]],
	"/2fa/activate": [16,[5]],
	"/2fa/verify": [17,[5]],
	"/(main)/(app)/channels": [7,[2,3,4]],
	"/(main)/(app)/channels/create": [9,[2,3,4]],
	"/(main)/(app)/channels/[id]": [8,[2,3,4]],
	"/(main)/(app)/friends": [10,[2,3]],
	"/(main)/game/[id]": [15,[2]],
	"/(main)/(app)/parameters": [11,[2,3]],
	"/(main)/(app)/postgame": [12,[2,3]],
	"/(main)/(app)/profile/[username]": [13,[2,3]],
	"/(main)/(app)/users": [14,[2,3]]
};

export const hooks = {
	handleError: (({ error }) => { console.error(error) }),
};