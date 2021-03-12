/*
 * imgBox - jQuery Plugin
 * Yet another lightbox alternative
 *
 * Copyright (c) 2009 jQueryGlobe
 * Examples and documentation at: http://jqueryglobe.com/article/imgbox/
 * 
 * Version: 1.0.0 (21/10/2009)
 * Requires: jQuery v1.3+
 * 
 * Dual licensed under the MIT and GPL licenses:
 *   http://www.opensource.org/licenses/mit-license.php
 *   http://www.gnu.org/licenses/gpl.html
 */

;(function($) {
    $.fn.fixPNG = function() {
        return this.each(function() {
            var b = $(this).css('backgroundImage');
            if (b.match(/^url\(["']?(.*\.png)["']?\)$/i)) {
                b = RegExp.$1;
                $(this).css({
                    'backgroundImage': 'none',
                    'filter': "progid:DXImageTransform.Microsoft.AlphaImageLoader(enabled=true, sizingMethod=" + ($(this).css('backgroundRepeat') == 'no-repeat' ? 'crop' : 'scale') + ", src='" + b + "')"
                }).each(function() {
                    var a = $(this).css('position');
                    if (a != 'absolute' && a != 'relative') $(this).css('position', 'relative')
                })
            }
        })
    };
    var g, opts, preloader, orig_pos, final_pos, busy = false,
        nr, zindex = 90,
        titleh = 0,
        shadow = 20,
        margin = 20,
        fx = $.extend($('<div/>')[0], {
            prop: 0
        });
    $.fn.imgbox = function(a) {
        return this.unbind('click.pb').bind('click.pb', function() {
            $.imgbox($(this), a);
            return false
        })
    };
    $.imgbox = function(e, o) {
        if (busy) {
            return false
        }
        g = e;
        opts = $.extend({}, $.fn.imgbox.defaults, o);
        nr = jQuery.data(g[0]);
        if ($('#imgbox-wrap-' + nr).length) {
            zoomOut();
            return false
        }
        hideActivity();
        if (opts.overlayShow) {
            $('#imgbox-overlay').unbind().stop().hide().css({
                'height': $(document).height(),
                'opacity': opts.overlayOpacity
            }).show()
        }
        preloader = new Image;
        preloader.src = $(g).attr('href');
        if (preloader.complete == false) {
            showActivity();
            $(preloader).unbind().one('load', function() {
                hideActivity();
                zoomIn()
            })
        } else {
            zoomIn()
        }
    };
    $.fn.imgbox.defaults = {
        padding: 10,
        alignment: 'auto',
        allowMultiple: true,
        autoScale: true,
        speedIn: 500,
        speedOut: 500,
        easingIn: 'swing',
        easingOut: 'swing',
        zoomOpacity: false,
        overlayShow: false,
        overlayOpacity: 0.5,
        hideOnOverlayClick: true,
        hideOnContentClick: true
    };

    function zoomIn() {
        busy = true;
        if (opts.allowMultiple == false) {
            $('.imgbox-wrap').remove();
            $('.imgbox-bg-wrap').remove()
        } else {
            zindex = zindex + 2
        }
        final_pos = getZoomTo();
        var a = $(g).attr('title') || '';
        $('<div id="imgbox-wrap-' + nr + '" class="imgbox-wrap"></div>').css({
            'z-index': zindex,
            'padding': opts.padding
        }).append('<img class="imgbox-img" id="imgbox-img-' + nr + '" src="' + preloader.src + '" alt="' + a + '" />').appendTo('body');
        $('<div id="imgbox-bg-' + nr + '" class="imgbox-bg-wrap"><div class="imgbox-bg imgbox-bg-n"/><div class="imgbox-bg imgbox-bg-ne"/><div class="imgbox-bg imgbox-bg-e"/><div class="imgbox-bg imgbox-bg-se"/><div class="imgbox-bg imgbox-bg-s"/><div class="imgbox-bg imgbox-bg-sw"/><div class="imgbox-bg imgbox-bg-w"/><div class="imgbox-bg imgbox-bg-nw"/></div>').appendTo('body');
        if ($.browser.msie && parseInt($.browser.version.substr(0, 1)) < 7) {
            $('#imgbox-bg-' + nr).find('.imgbox-bg').fixPNG()
        }
        titleh = 0;
        if (a.length > 0) {
            $('<div id="imgbox-tmp" class="imgbox-title" />').html(a).css('width', final_pos.width).appendTo('body');
            titleh = $('#imgbox-tmp').outerHeight();
            final_pos.height += titleh;
            final_pos.top -= titleh > margin + shadow ? margin : margin * 0.5;
            $('#imgbox-tmp').remove();
            $('#imgbox-wrap-' + nr).append('<div class="imgbox-title">' + a + '</div>')
        }
        if (opts.speedIn > 0) {
            var b = getThumbPos();
            orig_pos = {
                top: b.top - opts.padding,
                left: b.left - opts.padding,
                width: b.width,
                height: b.height
            };
            $('#imgbox-wrap-' + nr).css(orig_pos).show();
            $('#imgbox-bg-' + nr).css({
                top: orig_pos.top,
                left: orig_pos.left,
                width: orig_pos.width + (opts.padding * 2),
                height: orig_pos.height + (opts.padding * 2),
                'z-index': zindex - 1
            }).show();
            if (opts.zoomOpacity) {
                final_pos.opacity = 1
            }
            fx.prop = 0;
            $(fx).animate({
                prop: 1
            }, {
                duration: opts.speedIn,
                easing: opts.easingIn,
                step: draw,
                complete: _finish
            })
        } else {
            $('#imgbox-img-' + nr).css('height', (final_pos.height - titleh) + 'px');
            $('#imgbox-wrap-' + nr).css(final_pos).fadeIn('normal', _finish);
            $('#imgbox-bg-' + nr).css({
                top: final_pos.top,
                left: final_pos.left,
                width: final_pos.width + (opts.padding * 2),
                height: final_pos.height + (opts.padding * 2),
                'z-index': zindex - 1
            }).fadeIn('normal')
        }
    };

    function draw(a) {
        var b = Math.round(orig_pos.width + (final_pos.width - orig_pos.width) * a);
        var c = Math.round(orig_pos.height + (final_pos.height - orig_pos.height) * a);
        var d = Math.round(orig_pos.top + (final_pos.top - orig_pos.top) * a);
        var e = Math.round(orig_pos.left + (final_pos.left - orig_pos.left) * a);
        $('#imgbox-wrap-' + nr).css({
            'width': b + 'px',
            'height': c + 'px',
            'top': d + 'px',
            'left': e + 'px'
        });
        $('#imgbox-bg-' + nr).css({
            'width': Math.round(b + opts.padding * 2) + 'px',
            'height': Math.round(c + opts.padding * 2) + 'px',
            'top': d + 'px',
            'left': e + 'px'
        });
        $('#imgbox-img-' + nr).css('height', Math.round(c - ((((c - Math.min(orig_pos.height, final_pos.height)) * 100) / (Math.max(orig_pos.height - final_pos.height, final_pos.height - orig_pos.height)) * titleh / 100))) + 'px');
        if (typeof final_pos.opacity !== 'undefined') {
            var f = a < 0.3 ? 0.3 : a;
            $('#imgbox-wrap-' + nr).css('opacity', f);
            if ($.browser.msie == false) {
                $('#imgbox-bg-' + nr).css('opacity', f)
            }
        }
    };

    function _finish() {
        if (opts.overlayShow && opts.hideOnOverlayClick) {
            $('#imgbox-overlay').bind('click', {
                elem: g,
                nr: nr,
                opts: opts,
                titleh: titleh
            }, clickHandler)
        }
        $('#imgbox-wrap-' + nr).css('filter', '').bind('click', {
            elem: g,
            nr: nr,
            opts: opts,
            titleh: titleh
        }, clickHandler).append('<a href="javascript:;" class="imgbox-close"></a>').children('.imgbox-title').show();
        if ($.browser.msie && parseInt($.browser.version.substr(0, 1)) < 7) {
            $('#imgbox-wrap-' + nr).find('.imgbox-close').fixPNG()
        }
        busy = false
    };

    function clickHandler(e) {
        e.stopPropagation();
        if (e.target.className == 'imgbox-close' || (e.data.opts.hideOnOverlayClick && e.target.id == 'imgbox-overlay') || (e.data.opts.hideOnContentClick && e.target.className == 'imgbox-img' && ($(this).css('z-index') == zindex || $('.imgbox-img').length == 1))) {
            g = e.data.elem;
            nr = e.data.nr;
            opts = e.data.opts;
            titleh = e.data.titleh;
            zoomOut()
        } else if ($(this).css('z-index') < zindex) {
            $(this).next('.imgbox-bg-wrap').css('z-index', ++zindex);
            $(this).css('z-index', ++zindex)
        }
    };

    function zoomOut() {
        if (busy) {
            return false
        }
        busy = true;
        $('#imgbox-wrap-' + nr).children('.imgbox-close, .imgbox-title').remove();
        if (opts.speedOut > 0) {
            var a = getThumbPos();
            orig_pos = {
                top: a.top - opts.padding,
                left: a.left - opts.padding,
                width: a.width,
                height: a.height
            };
            var a = $('#imgbox-wrap-' + nr).position();
            final_pos = {
                top: a.top,
                left: a.left,
                width: $('#imgbox-wrap-' + nr).width(),
                height: $('#imgbox-wrap-' + nr).height()
            };
            if (opts.zoomOpacity) {
                final_pos.opacity = 0
            }
            setTimeout(function() {
                $('#imgbox-wrap-' + nr).css('z-index', 90);
                $('#imgbox-bg-' + nr).css('z-index', 90)
            }, opts.speedOut * 0.5);
            fx.prop = 1;
            $(fx).animate({
                prop: 0
            }, {
                duration: opts.speedIn,
                easing: opts.easingIn,
                step: draw,
                complete: _clean_up
            })
        } else {
            if (opts.overlayShow) {
                _clean_up()
            } else {
                $('#imgbox-bg-' + nr).fadeOut('fast');
                $('#imgbox-wrap-' + nr).fadeOut('fast', _clean_up)
            }
        }
    };

    function _clean_up() {
        $('#imgbox-bg-' + nr).stop().remove();
        $('#imgbox-wrap-' + nr).remove();
        zindex = zindex > 90 ? zindex - 2 : 90;
        if (opts.overlayShow) {
            $('#imgbox-overlay').unbind().stop().fadeOut(200)
        }
        busy = false
    };

    function getZoomTo() {
        var a = getViewport();
        var b = {
            width: preloader.width,
            height: preloader.height
        };
        var c = (opts.padding + shadow + margin) * 2;
        var d = (opts.padding + shadow + margin) * 2;
        if (opts.autoScale && (b.width > (a[0] - c) || b.height > (a[1] - d))) {
            var e = Math.min(Math.min(a[0] - c, b.width) / b.width, Math.min(a[1] - d, b.height) / b.height);
            b.width = Math.round(e * b.width);
            b.height = Math.round(e * b.height)
        }
        if (opts.alignment == 'center') {
            b.top = a[3] + ((a[1] - b.height - opts.padding * 2) * 0.5);
            b.left = a[2] + ((a[0] - b.width - opts.padding * 2) * 0.5)
        } else {
            var f = getThumbPos();
            b.top = f.top - ((b.height - f.height) * 0.5) - opts.padding;
            b.left = f.left - ((b.width - f.width) * 0.5) - opts.padding;
            b.top = b.top > a[3] + margin + shadow ? b.top : a[3] + margin + shadow;
            b.left = b.left > a[2] + margin + shadow ? b.left : a[2] + margin + shadow;
            b.top = b.top > a[1] + a[3] - (b.height + d) ? a[1] + a[3] - (b.height + (margin + shadow + opts.padding * 2)) : b.top;
            b.left = b.left > a[0] + a[2] - (b.width + c) ? a[0] + a[2] - (b.width + (margin + shadow + opts.padding * 2)) : b.left
        } if (opts.autoScale == false) {
            b.top = b.top > a[3] + shadow + margin ? b.top : a[3] + shadow + margin;
            b.left = b.left > a[2] + shadow + margin ? b.left : a[2] + shadow + margin
        }
        b.top = parseInt(b.top);
        b.left = parseInt(b.left);
        return b
    };

    function getViewport() {
        return [$(window).width(), $(window).height(), $(document).scrollLeft(), $(document).scrollTop()]
    };

    function getThumbPos() {
        var a = $(g).find('img').eq(0);
        var b = a.offset();
        b.top += parseFloat(a.css('paddingTop'));
        b.left += parseFloat(a.css('paddingLeft'));
        b.top += parseFloat(a.css('border-top-width'));
        b.left += parseFloat(a.css('border-left-width'));
        b.width = a.width();
        b.height = a.height();
        return b
    };

    function showActivity() {
        var a = getThumbPos(g);
        $('#imgbox-loading').css(a).show()
    };

    function hideActivity() {
        $(preloader).unbind();
        $('#imgbox-loading').hide()
    };

    function cancelLoading() {
        hideActivity();
        if (opts.overlayShow) {
            $('#imgbox-overlay').unbind().stop().fadeOut(200)
        }
    };

    function init() {
        $('<div id="imgbox-loading"><div></div></div><div id="imgbox-overlay"></div>').appendTo('body');
        $('#imgbox-loading').click(cancelLoading).find('div').css('opacity', 0.4)
    };
    $(document).ready(function() {
        init()
    })
})(jQuery);