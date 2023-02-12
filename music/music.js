let musicList = [
    {
        "name": "ふたりのきもちのほんとのひみつ",
        "url": "music/music/%E3%81%B5%E3%81%9F%E3%82%8A%E3%81%AE%E3%81%8D%E3%82%82%E3%81%A1%E3%81%AE%E3%81%BB%E3%82%93%E3%81%A8%E3%81%AE%E3%81%B2%E3%81%BF%E3%81%A4.mp3",
    },
    {
        "name": "キルミーのベイベー!",
        "url": "music/music/%E3%82%AD%E3%83%AB%E3%83%9F%E3%83%BC%E3%81%AE%E3%83%99%E3%82%A4%E3%83%99%E3%83%BC!.mp3",
    },
    {
        "name": "一命矣",
        "url": "music/music/%E4%B8%80%E5%91%BD%E7%9F%A3.mp3",
    },
    {
        "name": "九万字",
        "url": "music/music/%E4%B9%9D%E4%B8%87%E5%AD%97.mp3",
    },
    {
        "name": "你是",
        "url": "music/music/%E4%BD%A0%E6%98%AF.mp3",
    },
    {
        "name": "千里邀月",
        "url": "music/music/%E5%8D%83%E9%87%8C%E9%82%80%E6%9C%88.mp3",
    },
    {
        "name": "告辞",
        "url": "music/music/%E5%91%8A%E8%BE%9E.mp3",
    },
    {
        "name": "城南雨歇处",
        "url": "music/music/%E5%9F%8E%E5%8D%97%E9%9B%A8%E6%AD%87%E5%A4%84.mp3",
    },
    {
        "name": "夜曲",
        "url": "music/music/%E5%A4%9C%E6%9B%B2.mp3",
    },
    {
        "name": "大喜",
        "url": "music/music/%E5%A4%A7%E5%96%9C.mp3",
    },
    {
        "name": "寻找",
        "url": "music/music/%E5%AF%BB%E6%89%BE.mp3",
    },
    {
        "name": "山上雪",
        "url": "music/music/%E5%B1%B1%E4%B8%8A%E9%9B%AA.mp3",
    },
    {
        "name": "平安奇妙物语",
        "url": "music/music/%E5%B9%B3%E5%AE%89%E5%A5%87%E5%A6%99%E7%89%A9%E8%AF%AD.mp3",
    },
    {
        "name": "无与伦比的美丽",
        "url": "music/music/%E6%97%A0%E4%B8%8E%E4%BC%A6%E6%AF%94%E7%9A%84%E7%BE%8E%E4%B8%BD.mp3",
    },
    {
        "name": "月光",
        "url": "music/music/%E6%9C%88%E5%85%89.mp3",
    },
    {
        "name": "眉南边",
        "url": "music/music/%E7%9C%89%E5%8D%97%E8%BE%B9.mp3",
    },
    {
        "name": "秘宝",
        "url": "music/music/%E7%A7%98%E5%AE%9D.mp3",
    },
    {
        "name": "笑纳",
        "url": "music/music/%E7%AC%91%E7%BA%B3.mp3",
    },
    {
        "name": "花月成双",
        "url": "music/music/%E8%8A%B1%E6%9C%88%E6%88%90%E5%8F%8C.mp3",
    },
    {
        "name": "赐我",
        "url": "music/music/%E8%B5%90%E6%88%91.mp3",
    },
    {
        "name": "起风了",
        "url": "music/music/%E8%B5%B7%E9%A3%8E%E4%BA%86.mp3",
    },
    {
        "name": "野子",
        "url": "music/music/%E9%87%8E%E5%AD%90.mp3",
    },
    {
        "name": "长安幻世绘",
        "url": "music/music/%E9%95%BF%E5%AE%89%E5%B9%BB%E4%B8%96%E7%BB%98.mp3",
    },
    {
        "name": "闻妖",
        "url": "music/music/%E9%97%BB%E5%A6%96.mp3",
    },
    {
        "name": "青白",
        "url": "music/music/%E9%9D%92%E7%99%BD.mp3",
    },
]

let player = new Audio();
let music;
let title = document.title;
let loadMusic = ()=>{
    music = musicList[Math.floor(Math.random()*musicList.length)];
    player.src = music.url;
}
let toggle = ()=>{
    if(player.paused){
        player.play();
        document.title = music.name;
    }
    else {
        player.pause();
        document.title = title;
    }
}
player.addEventListener('ended', ()=>{
    loadMusic();
    player.play();
})