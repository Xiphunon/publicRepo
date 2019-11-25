const Discord = require('discord.js');
const {
    prefix,
    token,
} = require('./config.json');
const ytdl = require('ytdl-core');

const client = new Discord.Client();

const queue = new Map();

client.on('ready', () => {
    console.log(`Logged in as ${client.user.tag}!`);
});



client.on('message', async message => {
    if (!message.guild) return;
    if (message.content.startsWith(`${prefix}satan`)) {
        const user = message.mentions.users.first();
        if (user) {
            const member = message.guild.member(user);

            if (member) {

                message.channel.send
            }
        }
    }
});

client.on('message', async message => {
    if (!message.guild) return;
    if (!message.content.startsWith(prefix)) return;

    const serverQueue = queue.get(message.guild.id);

    const lowerCaseMessage = message.content.toLowerCase();

    if (lowerCaseMessage.startsWith(`${prefix}play`)) {
        //Play a song
        execute(message, serverQueue);
        return;
    } else if (lowerCaseMessage.startsWith(`${prefix}skip`)) {
        //Skip current song
        skip(message, serverQueue);
        return;
    } else if (lowerCaseMessage.startsWith(`${prefix}stop`)) {
        //Stop playing music
        stop(message, serverQueue);
        return;
    }
});

async function execute(message, serverQueue) {
    //Split message and create voice channel
    const args = message.content.split(' ');
    const voiceChannel = message.member.voiceChannel;

    //Check if user is connected to voice channel
    if (!voiceChannel) return message.channel.send('You need to be connected to a voice channel to play music.');
    const permissions = voiceChannel.permissionsFor(message.client.user);

    //Check if bot has permissions to play song
    if (!permissions.has('CONNECT') || !permissions.has('SPEAK')) {
        return message.channel.send('No permission to join and speak in your voice channel.');
    }

    //Get song info and save it
    const songInfo = await ytdl.getInfo(args[1]);
    const song = {
        title: songInfo.title,
        url: songInfo.video_url,
    };

    if (!serverQueue) {
        //If server queue is empty, play song

        //Create contract for queue
        const queueContruct = {
            textChannel: message.channel,
            voiceChannel: voiceChannel,
            connection: null,
            songs: [],
            volume: 5,
            playing: true,
        };

        //Set queue with contract
        queue.set(message.guild.id, queueContruct);
        //Push song to song array
        queueContruct.songs.push(song);

        try {
            //Try to join voice chat
            var connection = await voiceChannel.join();
            queueContruct.connection = connection;

            play(message.guild, queueContruct.songs[0]);
        } catch (err) {
            //Print error
            console.log(err);
            queue.delete(message.guild.id);
            return message.channel.send(err);
        }

    } else {
        //if server queue isn't empty, add song to queue
        serverQueue.songs.push(song);
        console.log(serverQueue.songs);
        return message.channel.send(`${song.title} has been added to the queue`);
    }
}

function play(guild, song) {
    const serverQueue = queue.get(guild.id);
    if (!song) {
        serverQueue.voiceChannel.leave();
        queue.delete(guild.id);
        return;
    }

    const dispatcher = serverQueue.connection.playStream(ytdl(song.url))
        .on('end', () => {
            console.log('Music ended');
            //Delete finished songs from queue
            serverQueue.songs.shift();
            //Play next song
            play(guild, serverQueue.songs[0]);
        })
        .on('error', error => {
            console.log(error);
        });
    dispatcher.setVolumeLogarithmic(serverQueue.volume / 5);
}

function skip(message, serverQueue) {
    if (!message.member.voiceChannel) return message.channel.send('You have to be in a voice channel to stop the music!');
    if (!serverQueue) return message.channel.send('There is no song that I could skip!');
    serverQueue.connection.dispatcher.end();
}

function stop(message, serverQueue) {
    if (!message.member.voiceChannel) return message.channel.send('You have to be in a voice channel to stop the music!');
    serverQueue.songs = [];
    serverQueue.connection.dispatcher.end();
}

client.login(token);