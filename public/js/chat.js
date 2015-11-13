var chatManager = function(datamcflyRef) {
    this.datamcflyRef = datamcflyRef;
};

chatManager.prototype = {
    chats: [], 
    getChat: function(fromNumber) {
        var foundChat = null;
        for (c = 0; c < this.chats.length; c++) {
            if (this.chats[c].from == fromNumber) {
                foundChat = this.chats[c];
            }
        }

        if (foundChat == null) {
            foundChat = new chat( this.datamcflyRef );
            foundChat.init(fromNumber);
            foundChat.displayTemplate();
            this.chats.push(foundChat);
        }
        return foundChat;
    },
    updateChats: function() {
        var _this = this;
        this.datamcflyRef.once('value', function (data) {
            data.forEach( function(message){                    
                var row = message.value();
                _this.getChat( row.fromNumber ).addMessage(
                    row.textMessage,
                    row.tstamp,
                    row.direction
                );
            });
        });
        this.datamcflyRef.on('added', function (data) {
            var row = data.value();
            _this.getChat( row.fromNumber ).addMessage(
                row.textMessage,
                row.tstamp,
                row.direction
            );
        });
    }
};

var chat = function(datamcflyRef) {
    this.datamcflyRef = datamcflyRef;
};
chat.prototype = {
    init: function(name) {
        this.from = name;
        this.chatName = 'chat-' + this.from;
        this.buttonName = 'submit-' + this.from;
        this.textName = 'reply-' + this.from;
    },
    replyMessage: function(message) {
        var _this = this;
        $.ajax({
            type: "POST",
            url: "/reply",
            data: {
                'To': this.from,
                'Body': message,
                'From': this.from
            },
            dataType: "json",
            success: function(data) {
                // your message was sent
            }
        });
    },
    displayTemplate: function() {
        var content = '<div class="chatName">Chat with ' + this.from + '</div> \
        <div class="messages" id="' + this.chatName + '"></div> \
        <div class="messageForm"><textarea id="' + this.textName + '"></textarea><button id="' + this.buttonName + '">Reply</button></div> \
      </div>';

        content = '<div class="chatWindow" id="' + this.tmplName + '">' + content + '</div>';

        $('#templateContainer').append(content);
        var _this = this;

        $('#' + this.buttonName).click(function() {
            _this.replyMessage($('#' + _this.textName).val());
            $('#' + _this.textName).val('');
        });
    },
    addMessage: function(message, tstamp, direction) {
        $('#' + this.chatName).append("<div class='message_" + direction + "'>" + message + "<div class='tstamp'>" + tstamp + "</div></div>");
        responsiveVoice.speak(message);
    }
};
