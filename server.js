const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const rest = require('./rest');

const app = express();

app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'view'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

app.use('/api', rest);

app.get('/', (req, res) => {
    res.render('index');
});

const PORT = process.env.PORT || 3001;
app.listen(PORT, () => {
    console.log(`Сервер запущен на порту ${PORT}`);
}); 