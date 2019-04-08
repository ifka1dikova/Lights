import React from 'react'; //This imports the react components into our html file
import ReactDOM from 'react-dom';

import App from './App'; //This imports the javascript file onto our webpage aswell
import * as serviceWorker from './serviceWorker';

ReactDOM.render(<App />, document.getElementById('root'));

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister();
